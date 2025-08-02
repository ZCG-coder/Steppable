#pragma once

#include "appState.hpp"

#include <imgui.h>

namespace steppable::__internals::gui
{
    constexpr float SMALL_FONT_SIZE = 12.0F;
    constexpr float NORMAL_FONT_SIZE = 16.0F;
    constexpr float LARGE_FONT_SIZE = 30.0F;

    void loadAllFonts(AppState* state) noexcept;

    enum class IconType : ImU32
    {
        Flow,
        Circle,
        Square,
        Grid,
        RoundSquare,
        Diamond
    };

    void icon(const ImVec2& size,
              IconType type,
              bool filled,
              const ImVec4& color /* = ImVec4(1, 1, 1, 1)*/,
              const ImVec4& innerColor /* = ImVec4(0, 0, 0, 0)*/);
} // namespace steppable::__internals::gui
