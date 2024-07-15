#pragma once

#include "output.hpp"

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <filesystem>
#include <imgui.h>
#include <string>

using namespace std::literals;

namespace steppable::gui::__internals
{
    inline void addIfExistent(const ImGuiIO* io,
                              const std::filesystem::path& path,
                              const ImFontConfig* config,
                              const ImWchar* ranges) noexcept
    {
        if (io->Fonts->Fonts.empty() and config->MergeMode)
            config = nullptr;
        if (std::filesystem::exists(path))
        {
#ifdef DEBUG
            output::info("addIfExistent"s, "Added font {0}"s, { path });
#endif
            io->Fonts->AddFontFromFileTTF(path.c_str(), 15.0F, config, ranges);
        }
    }

    inline void loadFonts(const ImGuiIO* io) noexcept
    {
        ImFontConfig config;
        config.MergeMode = true;
#ifdef WINDOWS
        // WINDOWS fonts
        // -------------
        // Chinese    -> Microsoft YaHei
        // Cyrillic   -> Segoe UI -----------------+
        // Greek      -> Segoe UI -----------------|
        // Japanese   -> Meiryo                    |
        // Korean     -> Malgun Gothic             +--> Top-priority
        // Thai       -> Leelawadee                |
        // Vietnamese -> Segoe UI -----------------+

        // Load top-priority fonts
        addIfExistent(io, "C:/Windows/Fonts/segoeui.ttf", &config, io->Fonts->GetGlyphRangesCyrillic());
        addIfExistent(io, "C:/Windows/Fonts/segoeui.ttf", &config, io->Fonts->GetGlyphRangesDefault());
        addIfExistent(io, "C:/Windows/Fonts/segoeui.ttf", &config, io->Fonts->GetGlyphRangesGreek());
        addIfExistent(io, "C:/Windows/Fonts/segoeui.ttf", &config, io->Fonts->GetGlyphRangesVietnamese());

        // Load Chinese fonts
        addIfExistent(io, "C:/Windows/Fonts/msyh.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());

        // Load Japanese fonts
        addIfExistent(io, "C:/Windows/Fonts/meiryo.ttc", &config, io->Fonts->GetGlyphRangesJapanese());

        // Load Korean fonts
        addIfExistent(io, "C:/Windows/Fonts/malgun.ttf", &config, io->Fonts->GetGlyphRangesKorean());

        // Load Thai fonts
        addIfExistent(io, "C:/Windows/Fonts/leelawad.ttf", &config, io->Fonts->GetGlyphRangesThai());
#elif defined(MACOSX)
        // MACOS fonts
        // -------------
        // Chinese    -> PingFang SC (*)
        // Cyrillic   -> SF Pro -----------------+
        // Greek      -> SF Pro -----------------|
        // Japanese   -> Hiragino Sans           |
        // Korean     -> Apple SD Gothic Neo     +--> Top-priority
        // Thai       -> Thonburi                |
        // Vietnamese -> SF Pro -----------------+
        //
        // (*) NOTE: PingFang may not be available on all systems, but STHeiti Medium is a good alternative.

        // Load top-priority fonts
        addIfExistent(io, "/Library/Fonts/SF-Pro.ttf", &config, io->Fonts->GetGlyphRangesCyrillic());
        addIfExistent(io, "/Library/Fonts/SF-Pro.ttf", &config, io->Fonts->GetGlyphRangesDefault());
        addIfExistent(io, "/Library/Fonts/SF-Pro.ttf", &config, io->Fonts->GetGlyphRangesGreek());
        addIfExistent(io, "/Library/Fonts/SF-Pro.ttf", &config, io->Fonts->GetGlyphRangesVietnamese());

        // Load Chinese fonts
        addIfExistent(io, "/System/Library/Fonts/PingFang.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());
        addIfExistent(io, "/System/Library/Fonts/STHeiti Medium.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());

        // Load Japanese fonts
        addIfExistent(io, "/System/Library/Fonts/Hiragino.ttc", &config, io->Fonts->GetGlyphRangesJapanese());

        // Load Korean fonts
        addIfExistent(io, "/System/Library/Fonts/AppleSDGothicNeo.ttc", &config, io->Fonts->GetGlyphRangesKorean());

        // Load Thai fonts
        addIfExistent(io, "/System/Library/Fonts/Thonburi.ttf", &config, io->Fonts->GetGlyphRangesThai());
        addIfExistent(io, "/System/Library/Fonts/Supplemental/Ayuthaya.ttf", &config, io->Fonts->GetGlyphRangesThai());
#elif defined(LINUX)
        // LINUX fonts
        // -------------
        // Chinese    -> WenQuanYi Zen Hei
        // Cyrillic   -> DejaVu Sans -----------------+
        // Greek      -> DejaVu Sans -----------------|
        // Japanese   -> Takao Gothic                 |
        // Korean     -> Nanum Gothic                 +--> Top-priority
        // Thai       -> Garuda                       |
        // Vietnamese -> DejaVu Sans -----------------+

        // Load top-priority fonts
        addIfExistent(io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesCyrillic());
        addIfExistent(io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesDefault());
        addIfExistent(io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesGreek());
        addIfExistent(io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesVietnamese());

        // Load Chinese fonts
        addIfExistent(io, "/usr/share/fonts/TTF/wqy-zenhei.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());

        // Load Japanese fonts
        addIfExistent(io, "/usr/share/fonts/TTF/takao-mincho.ttf", &config, io->Fonts->GetGlyphRangesJapanese());

        // Load Korean fonts
        addIfExistent(io, "/usr/share/fonts/TTF/NanumGothic.ttf", &config, io->Fonts->GetGlyphRangesKorean());

        // Load Thai fonts
        addIfExistent(io, "/usr/share/fonts/TTF/garuda.ttf", &config, io->Fonts->GetGlyphRangesThai());
#endif
        // Add the default font as well.
        io->Fonts->AddFontDefault(&config);
        io->Fonts->Build();
    }
} // namespace steppable::gui::__internals
