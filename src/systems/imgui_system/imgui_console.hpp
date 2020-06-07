#pragma once

#include <imgui.h>

#include <vector>

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

        void execCommand(const char* command_line);

        int textEditCallback(ImGuiInputTextCallbackData* data);

    private:

        char                        m_inputBuf[256];
        std::vector<char*>          m_items;
        std::vector<const char*>    m_commands;
        std::vector<char*>          m_history;
        int                         m_historyPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter             m_filter;
        bool                        m_autoScroll;
        bool                        m_scrollToBottom;

    };

}
