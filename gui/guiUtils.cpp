#include "imgui.h"
#include "output.hpp"

#include <filesystem>
#include <string>

using namespace std::literals;

void addFontIfExistent(const ImGuiIO* io,
                       const std::string& path,
                       const ImFontConfig* config,
                       const ImWchar* ranges) noexcept
{
    if (io->Fonts->Fonts.empty() and config->MergeMode)
        config = nullptr;
    if (std::filesystem::exists(path))
    {
#ifdef DEBUG
        steppable::output::info("addIfExistent"s, "Added font {0}"s, { path });
#endif
        io->Fonts->AddFontFromFileTTF(static_cast<const char*>(path.c_str()), 25.0F, config, ranges);
    }
}

void loadFonts(const ImGuiIO* io) noexcept
{
#ifdef HAS_FREETYPE
    steppable::output::info("loadFonts"s, "Loading fonts using FreeType"s);
#endif

    ImFontConfig config;
    config.MergeMode = true;
    config.RasterizerDensity = 2.0F;
    config.PixelSnapH = true;
    config.OversampleH = config.OversampleV = 3;

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
    addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesCyrillic());
    addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesGreek());
    addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesVietnamese());

    // Load Chinese fonts
    addFontIfExistent(io, "C:\\Windows\\Fonts\\msyh.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());

    // Load Japanese fonts
    addFontIfExistent(io, "C:\\Windows\\Fonts\\meiryo.ttc", &config, io->Fonts->GetGlyphRangesJapanese());

    // Load Korean fonts
    addFontIfExistent(io, "C:\\Windows\\Fonts\\malgun.ttf", &config, io->Fonts->GetGlyphRangesKorean());

    // Load Thai fonts
    addFontIfExistent(io, "C:\\Windows\\Fonts\\leelawad.ttf", &config, io->Fonts->GetGlyphRangesThai());

    addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesDefault());
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
    addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesCyrillic());
    addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesGreek());
    addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesVietnamese());

    // Load Chinese fonts
    addFontIfExistent(io, "/System/Library/Fonts/PingFang.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());
    addFontIfExistent(io, "/System/Library/Fonts/STHeiti Medium.ttc", &config, io->Fonts->GetGlyphRangesChineseFull());

    // Load Japanese fonts
    addFontIfExistent(io, "/System/Library/Fonts/Hiragino.ttc", &config, io->Fonts->GetGlyphRangesJapanese());

    // Load Korean fonts
    addFontIfExistent(io, "/System/Library/Fonts/AppleSDGothicNeo.ttc", &config, io->Fonts->GetGlyphRangesKorean());

    // Load Thai fonts
    addFontIfExistent(io, "/System/Library/Fonts/Thonburi.ttf", &config, io->Fonts->GetGlyphRangesThai());
    addFontIfExistent(io, "/System/Library/Fonts/Supplemental/Ayuthaya.ttf", &config, io->Fonts->GetGlyphRangesThai());

    addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesDefault());
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

    addIfExistent(io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesDefault());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MACOSX)
    // Add the default font as well.
    io->Fonts->AddFontDefault(&config);
#else
    io->Fonts->AddFontDefault();
#endif
    io->Fonts->Build();
    ImGui::GetIO().FontGlobalScale = 0.6F;
}
