/**************************************************************************************************
 * Copyright (c) 2023-2024 NWSOFT                                                                 *
 *                                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy                   *
 * of this software and associated documentation files (the "Software"), to deal                  *
 * in the Software without restriction, including without limitation the rights                   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                      *
 * copies of the Software, and to permit persons to whom the Software is                          *
 * furnished to do so, subject to the following conditions:                                       *
 *                                                                                                *
 * The above copyright notice and this permission notice shall be included in all                 *
 * copies or substantial portions of the Software.                                                *
 *                                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                  *
 * SOFTWARE.                                                                                      *
 **************************************************************************************************/

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
#ifdef MACOSX
    #include <CoreFoundation/CoreFoundation.h>

    bool isDarkModeEnabled()
    {
        bool isDarkMode = false;
        CFPreferencesAppSynchronize(CFSTR("AppleInterfaceStyle"));
        CFPropertyListRef value = CFPreferencesCopyAppValue(CFSTR("AppleInterfaceStyle"), kCFPreferencesAnyApplication);
        if (value != nullptr)
        {
            const auto* interfaceStyle = static_cast<CFStringRef>(value);
            if (CFStringCompare(interfaceStyle, CFSTR("Dark"), 0) == kCFCompareEqualTo)
                isDarkMode = true;
            CFRelease(value);
        }
        return isDarkMode;
    }
#elif defined(LINUX)
    bool isDarkModeEnabled() { return std::filesystem::exists("/usr/share/themes/Adwaita-dark/gtk-3.0"); }
#elif defined(WINDOWS)
    bool isDarkModeEnabled()
    {
        HKEY key;
        if (RegOpenKeyExA(HKEY_CURRENT_USER,
                          "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                          0,
                          KEY_QUERY_VALUE,
                          &key) == ERROR_SUCCESS)
        {
            DWORD value = 0;
            DWORD size = sizeof(DWORD);
            if (RegQueryValueExA(key, "AppsUseLightTheme", nullptr, nullptr, reinterpret_cast<LPBYTE>(&value), &size) ==
                ERROR_SUCCESS)
                return value == 0;
        }
        return false;
    }
#else
    bool isDarkModeEnabled() { return false; }
#endif

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
