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

#include <array>
#include <string>

namespace steppable::chem
{
    struct Element
    {
        int atomicNumber;
        std::string symbol;
        std::string name;
        float atomicMass;
        std::array<char, 6> cpkCol;
        std::string electronConf;
        float electroNeg;
        int atomicRadius;
        float ionizaEnergy;
        float electronAff;
        std::string oxidStates;
        std::string stdState;
        float meltPtK;
        float boilPtK;
        float density;
        std::string groupBlk;
        int yearDiscover;
        bool predicted;
        std::string electronShel;
        int numShells;

        Element(int atomicNumber);

        Element(const std::string& symbol);

        [[nodiscard]] std::string present() const { return symbol; }
    };

    struct Atom
    {
        Atom(const Element& elem, int neutrons = -1);

        [[nodiscard]] std::string present();

    private:
        Element elem;
        int protons = elem.atomicNumber;
        int neutrons = -1;
        int electrons = elem.atomicNumber;
    };

    struct Ion : private Atom
    {
        Ion(const Element& elem, int charge, int neutrons = -1);
    };
} // namespace steppable::chem
