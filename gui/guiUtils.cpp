#include "include/guiUtils.hpp"

#include "include/appState.hpp"
#include "include/fonts/codeicon.hpp"
#include "include/fonts/codeiconGlyphs.hpp"
#include "output.hpp"

#include <filesystem>
#include <imgui.h>
#include <string>

using namespace std::literals;

namespace steppable::__internals::gui
{
    namespace
    {
        ImFont* addFontIfExistent(const ImGuiIO* io,
                                  const std::string& path,
                                  const ImFontConfig* config,
                                  const ImWchar* ranges,
                                  const float& size) noexcept
        {
            ImFont* font = nullptr;
            if (std::filesystem::exists(path))
            {
#ifdef DEBUG
                steppable::output::info("addFontIfExistent"s, "Added font {0}"s, { path });
#endif
                font = io->Fonts->AddFontFromFileTTF(static_cast<const char*>(path.c_str()), size, config, ranges);
            }

            return font;
        }

        ImFont* loadFonts(const ImGuiIO* io, const float& size) noexcept
        {
#ifdef HAS_FREETYPE
            steppable::output::info("loadFonts"s, "Loading fonts using FreeType"s);
#endif

            ImFontConfig config;
            config.MergeMode = false;

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
            ImFont* font = addFontIfExistent(
                io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesCyrillic(), size);
            config.MergeMode = true;
            addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesGreek(), size);
            addFontIfExistent(
                io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesVietnamese(), size);

            // Load Chinese fonts
            addFontIfExistent(
                io, "C:\\Windows\\Fonts\\msyh.ttc", &config, io->Fonts->GetGlyphRangesChineseFull(), size);

            // Load Japanese fonts
            addFontIfExistent(io, "C:\\Windows\\Fonts\\meiryo.ttc", &config, io->Fonts->GetGlyphRangesJapanese(), size);

            // Load Korean fonts
            addFontIfExistent(io, "C:\\Windows\\Fonts\\malgun.ttf", &config, io->Fonts->GetGlyphRangesKorean(), size);

            // Load Thai fonts
            addFontIfExistent(io, "C:\\Windows\\Fonts\\leelawad.ttf", &config, io->Fonts->GetGlyphRangesThai(), size);

            addFontIfExistent(io, "C:\\Windows\\Fonts\\segoeui.ttf", &config, io->Fonts->GetGlyphRangesDefault(), size);
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
            ImFont* font = addFontIfExistent(
                io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesCyrillic(), size);
            config.MergeMode = true;
            addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesGreek(), size);
            addFontIfExistent(
                io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesVietnamese(), size);

            // Load Chinese fonts
            addFontIfExistent(
                io, "/System/Library/Fonts/PingFang.ttc", &config, io->Fonts->GetGlyphRangesChineseFull(), size);
            addFontIfExistent(
                io, "/System/Library/Fonts/STHeiti Medium.ttc", &config, io->Fonts->GetGlyphRangesChineseFull(), size);

            // Load Japanese fonts
            addFontIfExistent(
                io, "/System/Library/Fonts/Hiragino.ttc", &config, io->Fonts->GetGlyphRangesJapanese(), size);

            // Load Korean fonts
            addFontIfExistent(
                io, "/System/Library/Fonts/AppleSDGothicNeo.ttc", &config, io->Fonts->GetGlyphRangesKorean(), size);

            // Load Thai fonts
            addFontIfExistent(io, "/System/Library/Fonts/Thonburi.ttf", &config, io->Fonts->GetGlyphRangesThai(), size);
            addFontIfExistent(
                io, "/System/Library/Fonts/Supplemental/Ayuthaya.ttf", &config, io->Fonts->GetGlyphRangesThai(), size);

            addFontIfExistent(io, "/System/Library/Fonts/SFNS.ttf", &config, io->Fonts->GetGlyphRangesDefault(), size);
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
            ImFont* font = addFontIfExistent(
                io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesCyrillic(), size);
            config.MergeMode = true;
            addFontIfExistent(
                io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesGreek(), size);
            addFontIfExistent(
                io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesVietnamese(), size);

            // Load Chinese fonts
            addFontIfExistent(
                io, "/usr/share/fonts/TTF/wqy-zenhei.ttc", &config, io->Fonts->GetGlyphRangesChineseFull(), size);

            // Load Japanese fonts
            addFontIfExistent(
                io, "/usr/share/fonts/TTF/takao-mincho.ttf", &config, io->Fonts->GetGlyphRangesJapanese(), size);

            // Load Korean fonts
            addFontIfExistent(
                io, "/usr/share/fonts/TTF/NanumGothic.ttf", &config, io->Fonts->GetGlyphRangesKorean(), size);

            // Load Thai fonts
            addFontIfExistent(io, "/usr/share/fonts/TTF/garuda.ttf", &config, io->Fonts->GetGlyphRangesThai(), size);

            addFontIfExistent(
                io, "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", &config, io->Fonts->GetGlyphRangesDefault(), size);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MACOSX)
            // Add the default font as well.
            io->Fonts->AddFontDefault(&config);
#else
            io->Fonts->AddFontDefault();
#endif
            static const ImWchar icons_ranges[] = { ICON_MIN_CI, ICON_MAX_16_CI, 0 };
            const auto& prevGlyphMinAdvanceX = config.GlyphMinAdvanceX;
            config.PixelSnapH = true;
            config.GlyphMinAdvanceX = size;

            io->Fonts->AddFontFromMemoryCompressedTTF(
                codicon_compressed_data, codicon_compressed_size, size * 2.0F / 3.0F, &config, icons_ranges);

            config.GlyphMinAdvanceX = prevGlyphMinAdvanceX;
            config.PixelSnapH = false;
            config.MergeMode = false;

            return font;
        }

        void drawIcon(ImDrawList* drawList,
                      const ImVec2& a,
                      const ImVec2& b,
                      IconType type,
                      bool filled,
                      ImU32 color,
                      ImU32 innerColor)
        {
            auto rect = ImRect(a, b);
            auto rect_x = rect.Min.x;
            auto rect_y = rect.Min.y;
            auto rect_w = rect.Max.x - rect.Min.x;
            auto rect_h = rect.Max.y - rect.Min.y;
            auto rect_center_x = (rect.Min.x + rect.Max.x) * 0.5f;
            auto rect_center_y = (rect.Min.y + rect.Max.y) * 0.5f;
            auto rect_center = ImVec2(rect_center_x, rect_center_y);
            const auto outline_scale = rect_w / 24.0f;
            const auto extra_segments = static_cast<int>(2 * outline_scale); // for full circle

            if (type == IconType::Flow)
            {
                const auto origin_scale = rect_w / 24.0f;

                const auto offset_x = 1.0f * origin_scale;
                const auto offset_y = 0.0f * origin_scale;
                const auto margin = (filled ? 2.0f : 2.0f) * origin_scale;
                const auto rounding = 0.1f * origin_scale;
                const auto tip_round = 0.7f; // percentage of triangle edge (for tip)
                // const auto edge_round = 0.7f; // percentage of triangle edge (for corner)
                const auto canvas = ImRect(rect.Min.x + margin + offset_x,
                                           rect.Min.y + margin + offset_y,
                                           rect.Max.x - margin + offset_x,
                                           rect.Max.y - margin + offset_y);
                const auto canvas_x = canvas.Min.x;
                const auto canvas_y = canvas.Min.y;
                const auto canvas_w = canvas.Max.x - canvas.Min.x;
                const auto canvas_h = canvas.Max.y - canvas.Min.y;

                const auto left = canvas_x + canvas_w * 0.5f * 0.3f;
                const auto right = canvas_x + canvas_w - canvas_w * 0.5f * 0.3f;
                const auto top = canvas_y + canvas_h * 0.5f * 0.2f;
                const auto bottom = canvas_y + canvas_h - canvas_h * 0.5f * 0.2f;
                const auto center_y = (top + bottom) * 0.5f;
                // const auto angle = AX_PI * 0.5f * 0.5f * 0.5f;

                const auto tip_top = ImVec2(canvas_x + canvas_w * 0.5f, top);
                const auto tip_right = ImVec2(right, center_y);
                const auto tip_bottom = ImVec2(canvas_x + canvas_w * 0.5f, bottom);

                drawList->PathLineTo(ImVec2(left, top) + ImVec2(0, rounding));
                drawList->PathBezierCubicCurveTo(
                    ImVec2(left, top), ImVec2(left, top), ImVec2(left, top) + ImVec2(rounding, 0));
                drawList->PathLineTo(tip_top);
                drawList->PathLineTo(tip_top + (tip_right - tip_top) * tip_round);
                drawList->PathBezierCubicCurveTo(
                    tip_right, tip_right, tip_bottom + (tip_right - tip_bottom) * tip_round);
                drawList->PathLineTo(tip_bottom);
                drawList->PathLineTo(ImVec2(left, bottom) + ImVec2(rounding, 0));
                drawList->PathBezierCubicCurveTo(
                    ImVec2(left, bottom), ImVec2(left, bottom), ImVec2(left, bottom) - ImVec2(0, rounding));

                if (!filled)
                {
                    if (innerColor & 0xFF000000)
                        drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size, innerColor);

                    drawList->PathStroke(color, true, 2.0f * outline_scale);
                }
                else
                    drawList->PathFillConvex(color);
            }
            else
            {
                auto triangleStart = rect_center_x + 0.32f * rect_w;

                auto rect_offset = -static_cast<int>(rect_w * 0.25f * 0.25f);

                rect.Min.x += rect_offset;
                rect.Max.x += rect_offset;
                rect_x += rect_offset;
                rect_center_x += rect_offset * 0.5f;
                rect_center.x += rect_offset * 0.5f;

                if (type == IconType::Circle)
                {
                    const auto c = rect_center;

                    if (!filled)
                    {
                        const auto r = 0.5f * rect_w / 2.0f - 0.5f;

                        if (innerColor & 0xFF000000)
                            drawList->AddCircleFilled(c, r, innerColor, 12 + extra_segments);
                        drawList->AddCircle(c, r, color, 12 + extra_segments, 2.0f * outline_scale);
                    }
                    else
                    {
                        drawList->AddCircleFilled(c, 0.5f * rect_w / 2.0f, color, 12 + extra_segments);
                    }
                }

                if (type == IconType::Square)
                {
                    if (filled)
                    {
                        const auto r = 0.5f * rect_w / 2.0f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);

#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRectFilled(p0, p1, color, 0, ImDrawFlags_RoundCornersAll);
#else
                        drawList->AddRectFilled(p0, p1, color, 0, 15);
#endif
                    }
                    else
                    {
                        const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);

                        if (innerColor & 0xFF000000)
                        {
#if IMGUI_VERSION_NUM > 18101
                            drawList->AddRectFilled(p0, p1, innerColor, 0, ImDrawFlags_RoundCornersAll);
#else
                            drawList->AddRectFilled(p0, p1, innerColor, 0, 15);
#endif
                        }

#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRect(p0, p1, color, 0, ImDrawFlags_RoundCornersAll, 2.0f * outline_scale);
#else
                        drawList->AddRect(p0, p1, color, 0, 15, 2.0f * outline_scale);
#endif
                    }
                }

                if (type == IconType::Grid)
                {
                    const auto r = 0.5f * rect_w / 2.0f;
                    const auto w = ceilf(r / 3.0f);

                    const auto baseTl = ImVec2(floorf(rect_center_x - w * 2.5f), floorf(rect_center_y - w * 2.5f));
                    const auto baseBr = ImVec2(floorf(baseTl.x + w), floorf(baseTl.y + w));

                    auto tl = baseTl;
                    auto br = baseBr;
                    for (int i = 0; i < 3; ++i)
                    {
                        tl.x = baseTl.x;
                        br.x = baseBr.x;
                        drawList->AddRectFilled(tl, br, color);
                        tl.x += w * 2;
                        br.x += w * 2;
                        if (i != 1 || filled)
                            drawList->AddRectFilled(tl, br, color);
                        tl.x += w * 2;
                        br.x += w * 2;
                        drawList->AddRectFilled(tl, br, color);

                        tl.y += w * 2;
                        br.y += w * 2;
                    }

                    triangleStart = br.x + w + 1.0f / 24.0f * rect_w;
                }

                if (type == IconType::RoundSquare)
                {
                    if (filled)
                    {
                        const auto r = 0.5f * rect_w / 2.0f;
                        const auto cr = r * 0.5f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);

#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRectFilled(p0, p1, color, cr, ImDrawFlags_RoundCornersAll);
#else
                        drawList->AddRectFilled(p0, p1, color, cr, 15);
#endif
                    }
                    else
                    {
                        const auto r = 0.5f * rect_w / 2.0f - 0.5f;
                        const auto cr = r * 0.5f;
                        const auto p0 = rect_center - ImVec2(r, r);
                        const auto p1 = rect_center + ImVec2(r, r);

                        if (innerColor & 0xFF000000)
                        {
#if IMGUI_VERSION_NUM > 18101
                            drawList->AddRectFilled(p0, p1, innerColor, cr, ImDrawFlags_RoundCornersAll);
#else
                            drawList->AddRectFilled(p0, p1, innerColor, cr, 15);
#endif
                        }

#if IMGUI_VERSION_NUM > 18101
                        drawList->AddRect(p0, p1, color, cr, ImDrawFlags_RoundCornersAll, 2.0f * outline_scale);
#else
                        drawList->AddRect(p0, p1, color, cr, 15, 2.0f * outline_scale);
#endif
                    }
                }
                else if (type == IconType::Diamond)
                {
                    if (filled)
                    {
                        const auto r = 0.607f * rect_w / 2.0f;
                        const auto c = rect_center;

                        drawList->PathLineTo(c + ImVec2(0, -r));
                        drawList->PathLineTo(c + ImVec2(r, 0));
                        drawList->PathLineTo(c + ImVec2(0, r));
                        drawList->PathLineTo(c + ImVec2(-r, 0));
                        drawList->PathFillConvex(color);
                    }
                    else
                    {
                        const auto r = 0.607f * rect_w / 2.0f - 0.5f;
                        const auto c = rect_center;

                        drawList->PathLineTo(c + ImVec2(0, -r));
                        drawList->PathLineTo(c + ImVec2(r, 0));
                        drawList->PathLineTo(c + ImVec2(0, r));
                        drawList->PathLineTo(c + ImVec2(-r, 0));

                        if (innerColor & 0xFF000000)
                            drawList->AddConvexPolyFilled(drawList->_Path.Data, drawList->_Path.Size, innerColor);

                        drawList->PathStroke(color, true, 2.0f * outline_scale);
                    }
                }
                else
                {
                    const auto triangleTip = triangleStart + rect_w * (0.45f - 0.32f);

                    drawList->AddTriangleFilled(ImVec2(ceilf(triangleTip), rect_y + rect_h * 0.5f),
                                                ImVec2(triangleStart, rect_center_y + 0.15f * rect_h),
                                                ImVec2(triangleStart, rect_center_y - 0.15f * rect_h),
                                                color);
                }
            }
        }
    } // namespace

    void loadAllFonts(AppState* state) noexcept
    {
        auto& io = ImGui::GetIO();
        state->fontMgr.mainFont = loadFonts(&io, NORMAL_FONT_SIZE);
        state->fontMgr.titleFont = loadFonts(&io, LARGE_FONT_SIZE);
        state->fontMgr.smallFont = loadFonts(&io, SMALL_FONT_SIZE);
    }

    void icon(const ImVec2& size, IconType type, bool filled, const ImVec4& color, const ImVec4& innerColor)
    {
        if (ImGui::IsRectVisible(size))
        {
            const auto& cursorPos = ImGui::GetCursorScreenPos();
            const auto& drawList = ImGui::GetWindowDrawList();
            drawIcon(drawList, cursorPos, cursorPos + size, type, filled, ImColor(color), ImColor(innerColor));
        }

        ImGui::Dummy(size);
    }
} // namespace steppable::__internals::gui
