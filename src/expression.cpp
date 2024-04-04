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

// Finding operators
#include "number.hpp"

#include <cctype>
#include <stack>
#include <string>

using namespace steppable;

int operators(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// The maths
Number maths(Number a, Number b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return { "0" };
}

// Returning value of expression
std::string evaluate(std::string tokens)
{
    int i;

    // stack to store integers and operators.
    std::stack<Number> numbers;
    std::stack<char> ops;

    for (i = 0; i < tokens.length(); i++)
    {
        // if token blank, skip
        if (tokens[i] == ' ')
            continue;

        // if token '(' add to stack
        else if (tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }

        // if token is a number, add to stack
        else if (isalnum(tokens[i]))

        {
            std::string val;
            // single or double digit number.
            while (i < tokens.length() && isalnum(tokens[i]))
            {
                val += tokens[i];
                i++;
            }

            numbers.push(Number(val));
        }

        // if token ')', solve entire brace.
        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                auto val2 = numbers.top();
                numbers.pop();

                auto val1 = numbers.top();
                numbers.pop();

                char op = ops.top();
                ops.pop();

                numbers.push(maths(val1, val2, op));
            }

            // pop opening brace.
            ops.pop();
        }

        // Current token is an operator.
        else
        {
            while (!ops.empty() && operators(ops.top()) >= operators(tokens[i]))
            {
                auto val2 = numbers.top();
                numbers.pop();

                auto val1 = numbers.top();
                numbers.pop();

                char op = ops.top();
                ops.pop();

                numbers.push(maths(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

    // Do remaining operations
    while (!ops.empty())
    {
        auto val2 = numbers.top();
        numbers.pop();

        auto val1 = numbers.top();
        numbers.pop();

        char op = ops.top();
        ops.pop();

        numbers.push(maths(val1, val2, op));
    }

    // Top of 'numbers' contains result, return
    return numbers.top().present();
}
