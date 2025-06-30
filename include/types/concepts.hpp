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

/**
 * @brief Defines concepts to be used for distinguishing types in the project.
 * @author Andy Zhang
 * @date 23 Jun 2025
 */

#include <concepts>
#include <ostream>
#include <string>

/**
 * @namespace steppable::concepts
 * @brief Defines concepts to be used for distinguishing types in the project.
 */
namespace steppable::concepts
{
    template<typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>; ///< Represents any C++ numeral literals.

    template<typename ObjectT>
    /// @brief Represents any object with a `.present()` method.
    concept Presentable = requires(ObjectT object) {
        { object.present() } -> std::same_as<std::string>;
    };

    template<typename ObjectT>
    /// @brief Represents any streams with a `.operator<<()` method.
    concept Stream = requires(ObjectT object) {
        { object.operator<<() } -> std::same_as<std::ostream&>;
    };
} // namespace steppable::concepts
