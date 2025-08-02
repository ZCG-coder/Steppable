#pragma once

#include <cstdarg>
#include <imgui.h>

struct FontManager
{
    ImFont* mainFont;
    ImFont* titleFont;
    ImFont* smallFont;

    void titleText(const char* fmt, ...) const
    {
        va_list args = nullptr;
        va_start(args, fmt);

        ImGui::PushFont(titleFont);
        ImGui::Text(fmt, args);
        ImGui::PopFont();

        va_end(args);
    }
};
