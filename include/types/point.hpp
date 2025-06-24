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

#include <cstddef>

namespace steppable
{
    /**
     * @struct XYPoint
     * @brief A point object
     * @details Represents a 2-D point on a 2D plane.
     */
    struct XYPoint
    {
        size_t x = 0;
        size_t y = 0;
    };

    /**
     * @struct YXPoint
     * @brief A point object
     * @details Represents a 2-D point on a 2D plane.
     */
    struct YXPoint
    {
        size_t y = 0;
        size_t x = 0;
    };

    /**
     * @struct YX2Points
     * @brief A points object that represents two points
     * @details Represents two 2-D points on a 2D plane.
     */
    struct YX2Points
    {
        size_t y1 = 0;
        size_t x1 = 0;
        size_t y2 = 0;
        size_t x2 = 0;
    };
} // namespace steppable
