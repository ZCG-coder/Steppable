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

#include "constants.hpp"

#include <string_view>

// NOLINTBEGIN(cert-err58-cpp)
namespace steppable::constants
{
    const std::string_view& PI =
        "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    const std::string_view& TWO_PI = "6.283185307179586231995926937088370323181152343750";
    const std::string_view& PI_OVER_2 =
        "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412835292542";
    const std::string_view& PI_OVER_180 =
        "0.01745329251994329508887757482524547311994764539930555555555555555555555555555555555555555555555555556";
    const std::string_view& PI_OVER_200 =
        "0.01570796326794896619231321691639716312084074699687552942986246296153903203140449499314017412671058534";
    const std::string_view& E = "2.718281828459045090795598298427648842334747314453125";
} // namespace steppable::constants
// NOLINTEND(cert-err58-cpp)
