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

#include "fn/_calc.hpp"

/**
 * @brief Wrappers around internal Steppable functions to allow operating with Steppable `Number` objects.
 * @namespace steppable::fn
 */
namespace steppable::fn
{
    /**
     * @brief Calculates the cosine of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the cosine of.
     *
     * @return The cosine of the Steppable `Number` object.
     */
    inline Number cos(const Number& x)
    {
      return __internals::calc::cos(x.present(), static_cast<int>(x.getDecimals()));
    }

    /**
     * @brief Calculates the sine of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the sine of.
     *
     * @return The sine of the Steppable `Number` object.
     */
    Number sin(const Number& x);

    /**
     * @brief Calculates the tangent of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the tangent of.
     *
     * @return The tangent of the Steppable `Number` object.
     */
    Number tan(const Number& x);

    /**
     * @brief Calculates the secant of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the secant of.
     *
     * @return The secant of the Steppable `Number` object.
     */
    Number sec(const Number& x);

    /**
     * @brief Calculates the cosecant of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the cosecant of.
     *
     * @return The cosecant of the Steppable `Number` object.
     */
    Number csc(const Number& x);

    /**
     * @brief Calculates the cotangent of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the cotangent of.
     *
     * @return The cotangent of the Steppable `Number` object.
     */
    Number cot(const Number& x);

    /**
     * @brief Calculates the arc cosine of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc cosine of.
     *
     * @return The arc cosine of the Steppable `Number` object.
     */
    Number acos(const Number& x);

    /**
     * @brief Calculates the arc sine of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc sine of.
     *
     * @return The arc sine of the Steppable `Number` object.
     */
    Number asin(const Number& x);

    /**
     * @brief Calculates the arc tangent of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc tangent of.
     *
     * @return The arc tangent of the Steppable `Number` object.
     */
    Number atan(const Number& x);

    /**
     * @brief Calculates the arc secant of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc secant of.
     *
     * @return The arc secant of the Steppable `Number` object.
     */
    Number asec(const Number& x);

    /**
     * @brief Calculates the arc cosecant of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc cosecant of.
     *
     * @return The arc cosecant of the Steppable `Number` object.
     */
    Number acsc(const Number& x);

    /**
     * @brief Calculates the arc cotangent of a Steppable `Number` object.
     *
     * @param x The Steppable `Number` object to calculate the arc cotangent of.
     *
     * @return The arc cotangent of the Steppable `Number` object.
     */
    Number acot(const Number& x);

    /**
     * @brief Hyperbolic sine function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic sine of the Steppable `Number` object.
     */
    Number sinh(const Number& x);

    /**
     * @brief Hyperbolic cosine function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic cosine of the Steppable `Number` object.
     */
    Number cosh(const Number& x);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic tangent of the Steppable `Number` object.
     */
    Number tanh(const Number& x);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic tangent of the Steppable `Number` object.
     */
    Number sech(const Number& x);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic tangent of the Steppable `Number` object.
     */
    Number csch(const Number& x);

    /**
     * @brief Hyperbolic tangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The hyperbolic tangent of the Steppable `Number` object.
     */
    Number coth(const Number& x);

    /**
     * @brief Inverse hyperbolic sine function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic sine of the Steppable `Number` object.
     */
    Number asinh(const Number& x);

    /**
     * @brief Inverse hyperbolic cosine function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic cosine of the Steppable `Number` object.
     */
    Number acosh(const Number& x);

    /**
     * @brief Inverse hyperbolic tangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic tangent of the Steppable `Number` object.
     */
    Number atanh(const Number& x);

    /**
     * @brief Inverse hyperbolic cotangent function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic cotangent of the Steppable `Number` object.
     */
    Number acoth(const Number& x);

    /**
     * @brief Inverse hyperbolic secant function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic secant of the Steppable `Number` object.
     */
    Number asech(const Number& x);

    /**
     * @brief Inverse hyperbolic cosecant function.
     *
     * @param x The Steppable `Number` object.
     *
     * @return The inverse hyperbolic cosecant of the Steppable `Number` object.
     */
    Number acsch(const Number& x);

    /**
     * @brief Calculates the logarithm with a given base.
     *
     * @param _number The Steppable `Number` object to calculate the logarithm of.
     * @param _base The base of the logarithm.
     * @return The result of the logarithm operation.
     */
    Number logb(const Number& _number, const Number& _base);

    /**
     * @brief Calculates the common logarithm of a Steppable `Number` object.
     *
     * @note The common logarithm is the logarithm with base 10.
     *
     * @param _number The Steppable `Number` object to calculate the common logarithm of.
     * @return The result of the common logarithm operation.
     */
    Number log10(const Number& _number);

    /**
     * @brief Calculates the binary logarithm of a Steppable `Number` object.
     *
     * @note The binary logarithm is the logarithm with base 2.
     *
     * @param _number The Steppable `Number` object to calculate the binary logarithm of.
     * @return The result of the binary logarithm operation.
     */
    Number log2(const Number& _number);

    /**
     * @brief Calculates the natural logarithm of a Steppable `Number` object.
     *
     * @note The natural logarithm is the logarithm with base e.
     *
     * @param _number The Steppable `Number` object to calculate the natural logarithm of.
     * @return The result of the natural logarithm operation.
     */
    Number ln(const Number& _number);
}