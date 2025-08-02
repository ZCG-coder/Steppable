#pragma once

#include <imgui.h>
#include <string>

namespace steppable::__internals::gui
{
    void addFontIfExistent(const ImGuiIO* io,
                           const std::string& path,
                           const ImFontConfig* config,
                           const ImWchar* ranges) noexcept;

    void loadFonts(const ImGuiIO* io) noexcept;
} // namespace steppable::__internals::gui
