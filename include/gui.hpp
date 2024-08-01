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

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <filesystem>
#include <functional>
#include <imgui.h>
#include <string>

using namespace std::literals;

/**
 * @brief The namespace for the internal components of the GUI module of the Steppable library.
 * @details This namespace contains the internal components of the GUI module of the Steppable library.
 * For example, methods that gets the system fonts, checks if the dark mode is enabled, and loads the fonts.
 * @note This namespace is not intended for use by the end user.
 */
namespace steppable::gui::__internals
{
    /**
     * @brief Checks if the dark mode is enabled.
     * @return True if the dark mode is enabled, false otherwise.
     */
    bool isDarkModeEnabled();

    /**
     * Attempts to add a font to the application if it exists in the system.
     *
     * This method checks if a specified font is available on the system. If the font is found,
     * it is added to the application's font resources, making it available for use within the application.
     * If the font does not exist, the method will not perform any action or may log an error or warning,
     * depending on implementation details.
     *
     * @param io A pointer to an ImGuiIO object to enable configuration.
     * @param path The absolute path to the font file.
     * @param config A pointer to an ImFontConfig object to enable font configuration.
     * @param ranges A pointer to an array of ImWchar objects to enable character range configuration.
     */
    void addFontIfExistent(const ImGuiIO* io,
                           const std::filesystem::path& path,
                           const ImFontConfig* config,
                           const ImWchar* ranges) noexcept;

    /**
     * @brief Loads the fonts for the application.
     * @details This method tries to find the system fonts that can display most character sets.
     * @param io A pointer to an ImGuiIO object to enable configuration
     */
    void loadFonts(const ImGuiIO* io) noexcept;
} // namespace steppable::gui::__internals

/**
 * @brief The namespace for the GUI components of the Steppable library. This is the main namespace for the GUI
 * components.
 */
namespace steppable::gui
{
    /**
     * @brief Runs the main window of the application.
     * @details This method replaces the long ininitalization process of the application with a simple
     * call to the runWindow method. This method initializes the SDL2 and OpenGL backends for the application,
     * then runs the main window loop. The main window loop is responsible for rendering the application's
     * contents and handling user input.
     *
     * @param name The name of the window.
     * @param predicate The function that will be called to render the window.
     */
    void runWindow(const std::string& name, const std::function<void(void)>& predicate);
} // namespace steppable::gui
