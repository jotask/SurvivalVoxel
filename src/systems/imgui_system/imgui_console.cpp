#include "imgui_console.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>

namespace aiko
{

    // Portable helpers
    static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
    static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
    static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
    static void  Strtrim(char* str) { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

    AikoConsole::AikoConsole()
        : m_historyPos(-1)
        , m_autoScroll (true)
        , m_scrollToBottom (false)
    {
        clearLog();
        m_commands.push_back("HELP");
        m_commands.push_back("HISTORY");
        m_commands.push_back("CLEAR");
        m_commands.push_back("CLASSIFY");  // "classify" is only here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
        addLog("Welcome to the console!");
    }

    AikoConsole::~AikoConsole()
    {
        clearLog();
    }

    void AikoConsole::clearLog()
    {
        m_items.clear();
    }

    void AikoConsole::addLog(const char* fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf) - 1] = 0;
        va_end(args);
        m_items.push_back(Strdup(buf));
    }

    void AikoConsole::draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        if (ImGui::Begin(title, p_open) == false)
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar. So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close Console"))
            {
                *p_open = false;
            }
            ImGui::EndPopup();
        }

        ImGui::TextWrapped("Aiko Console");
        ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

        // TODO: display items starting from the bottom

        if (ImGui::SmallButton("Add Dummy Text"))
        {
            addLog("%d some text", m_items.size());
            addLog("some more text");
            addLog("display very important message here!");
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Add Dummy Error"))
        {
            addLog("[error] something went wrong");
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear"))
        {
            clearLog();
        }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy");
        ImGui::SameLine();

        static auto printSpam = false;
        ImGui::Checkbox("PrintSpam", &printSpam);
        ImGui::SameLine();

        if (printSpam == true)
        {
            static float t = 0.0f;
            if (ImGui::GetTime() - t > 0.02f)
            {
                t = ImGui::GetTime();
                addLog("Spam %f", t);
            }
        }

        ImGui::Separator();

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &m_autoScroll);
            ImGui::EndPopup();
        }

        // Options, Filter
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        m_filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::Separator();

        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) clearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
        // You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
        // To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
        //     ImGuiListClipper clipper(Items.Size);
        //     while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
        // If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < m_items.size(); i++)
        {
            const char* item = m_items[i].c_str();
            if (!m_filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
            bool pop_color = false;
            if (strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
            ImGui::TextUnformatted(item);
            if (pop_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        if (m_scrollToBottom || (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        m_scrollToBottom = false;

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        bool reclaim_focus = false;

        auto textEditCallbackStub = [](ImGuiInputTextCallbackData* data)
        {
            auto* console = static_cast<AikoConsole*>(data->UserData);
            return console->textEditCallback(data);
        };

        if (ImGui::InputText("Input", &m_inputBuf[0], m_inputBuf.size(), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, textEditCallbackStub, (void*)this))
        {
            char* s = m_inputBuf.data();
            Strtrim(s);
            if (s[0])
                execCommand(s);
            strcpy(s, "");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

        ImGui::End();
    }

    void AikoConsole::execCommand(const std::string command_line)
    {
        addLog("# %s\n", command_line.c_str());

        // Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
        m_historyPos = -1;
        for (int i = m_history.size() - 1; i >= 0; i--)
        {
            if (m_history[i] == command_line)
            {
                m_history.erase(m_history.begin() + i);
                break;
            }
        }
        m_history.push_back(Strdup(command_line.c_str()));

        // Process command
        if (isStringEquals(command_line, "CLEAR"))
        {
            clearLog();
        }
        else if (isStringEquals(command_line, "HELP"))
        {
            addLog("Commands:");
            for (int i = 0; i < m_commands.size(); i++)
                addLog("- %s", m_commands[i]);
        }
        else if (isStringEquals(command_line, "HISTORY"))
        {
            int first = m_history.size() - 10;
            for (int i = first > 0 ? first : 0; i < m_history.size(); i++)
                addLog("%3d: %s\n", i, m_history[i]);
        }
        else
        {
            addLog("Unknown command: '%s'\n", command_line.c_str());
        }

        // On commad input, we scroll to bottom even if AutoScroll==false
        m_scrollToBottom = true;
    }

    int AikoConsole::textEditCallback(ImGuiInputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            std::vector<std::string> candidates;
            for (int i = 0; i < m_commands.size(); i++)
                if (Strnicmp(m_commands[i].c_str(), word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(m_commands[i].c_str());

            if (candidates.size() == 0)
            {
                // No match
                addLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.size() == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0].c_str());
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.size() && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0].c_str(), candidates[0].c_str() + match_len);
                }

                // List matches
                addLog("Possible matches:\n");
                for (int i = 0; i < candidates.size(); i++)
                    addLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = m_historyPos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (m_historyPos == -1)
                    m_historyPos = m_history.size() - 1;
                else if (m_historyPos > 0)
                    m_historyPos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (m_historyPos != -1)
                    if (++m_historyPos >= m_history.size())
                        m_historyPos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != m_historyPos)
            {
                const char* history_str = (m_historyPos >= 0) ? m_history[m_historyPos].c_str() : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
        }
        return 0;
    }

    bool AikoConsole::isStringEquals(const std::string & a, const std::string & b)
    {
        auto lamba = [](char a, char b) { return tolower(a) == tolower(b); };
        return std::equal(a.begin(), a.end(), b.begin(), b.end(), lamba);
    }

}
