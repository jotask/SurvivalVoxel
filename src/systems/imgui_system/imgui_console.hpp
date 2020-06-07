#pragma once

#include <imgui.h>

#include <vector>
#include <array>
#include <string>

namespace aiko
{
    class AikoConsole
    {
    public:

        AikoConsole();

        ~AikoConsole();

        void clearLog();

        void addLog(const char* fmt, ...);

        void draw(const char* title, bool* p_open);

    private:

        void execCommand(const std::string command_line);
        int textEditCallback(ImGuiInputTextCallbackData* data);
        bool isStringEquals(const std::string& a, const std::string& b);
        bool containsString(const std::string&, const std::string&);

        std::array<char, 256>           m_inputBuf;
        std::vector<std::string>        m_items;
        std::vector<std::string>        m_history;
        int                             m_historyPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter                 m_filter;
        bool                            m_autoScroll;
        bool                            m_scrollToBottom;

    };

}
