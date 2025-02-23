/**************************************************************************************************
 * Copyright (c) 2023-2025 NWSOFT                                                                 *
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

#include <string>
#include <vector>

/**
 * @namespace steppable::localization
 * @brief The namespace for the localization utilities.
 */
namespace steppable::localization
{
    /**
     * @brief Gets a string from origin, and by the key.
     * @details The origin is the name of the file, and the key is the GUID of the string.
     *
     * @param origin The name of the file, without the extension.
     * @param key The GUID key of the string.
     *
     * @return The string in its localized form.
     */
    std::string $(const std::string& origin, const std::string& key);

    /**
     * @brief Gets a string from origin, and by the key. Formats it with the format strings.
     * @details The origin is the name of the file, and the key is the GUID of the string. This method also
     * enables you to format the string with the format strings.
     *
     * @param origin The name of the file, without the extension.
     * @param formatKey The GUID key of the format string.
     * @param formatStrings The format strings to format the string with.
     * @return The formatted string in its localized form, formatted with the format strings.
     */
    std::string $(const std::string& origin,
                  const std::string& formatKey,
                  const std::vector<std::string>& formatStrings);
} // namespace steppable::localization
