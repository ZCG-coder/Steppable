/**************************************************************************************************
 * Copyright (c) 2023-2026 NWSOFT                                                                 *
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

#include "colors.hpp"
#include "platform.hpp"
#include "rounding.hpp"
#include "stpSqlite.hpp"
#include "symbols.hpp"

#include <array>
#include <string>
#include <vector>

namespace steppable::chem
{
    class Subshell
    {
        int order;
        char type;
        int electrons;

        friend class Element;

    public:
        [[nodiscard]] std::string present() const { return std::to_string(order) + type + std::to_string(electrons); }

        [[nodiscard]] int getOrder() const { return order; }
        [[nodiscard]] char getType() const { return type; }
        [[nodiscard]] int getElectrons() const { return electrons; }
    };

    class Element : private sqlite::STP_DataConnectorBase
    {
        friend class Atom;

        int atomicNumber;
        std::string symbol;
        std::string name;
        double atomicMass;
        std::array<char, 6> cpkCol = {};
        std::vector<Subshell> electronConf;
        double electroNeg;
        int atomicRadius;
        double ionizaEnergy;
        double electronAff;
        std::string oxidStates;
        std::string stdState;
        double meltPtK;
        double boilPtK;
        double density;
        std::string groupBlk;
        int yearDiscover;
        bool predicted;
        std::vector<int> electronShells;
        int numShells;

    public:
        Element(int atomicNumber);

        Element(const std::string& symbol);

        [[nodiscard]] int getAtomicNumber() const { return atomicNumber; }
        [[nodiscard]] std::string getSymbol() const { return symbol; }
        [[nodiscard]] std::string getName() const { return name; }
        [[nodiscard]] double getAtomicMass() const { return atomicMass; }
        [[nodiscard]] std::array<char, 6> getCpkCol() const { return cpkCol; }
        [[nodiscard]] std::vector<Subshell> getElectronConf() const { return electronConf; }
        [[nodiscard]] double getElectroNeg() const { return electroNeg; }
        [[nodiscard]] int getAtomicRadius() const { return atomicRadius; }
        [[nodiscard]] double getIonizaEnergy() const { return ionizaEnergy; }
        [[nodiscard]] double getElectronAff() const { return electronAff; }
        [[nodiscard]] std::string getOxidStates() const { return oxidStates; }
        [[nodiscard]] std::string getStdState() const { return stdState; }
        [[nodiscard]] double getMeltPtK() const { return meltPtK; }
        [[nodiscard]] double getBoilPtK() const { return boilPtK; }
        [[nodiscard]] double getDensity() const { return density; }
        [[nodiscard]] std::string getGroupBlk() const { return groupBlk; }
        [[nodiscard]] int getYearDiscover() const { return yearDiscover; }
        [[nodiscard]] bool getPredicted() const { return predicted; }
        [[nodiscard]] std::vector<int> getElectronShel() const { return electronShells; }
        [[nodiscard]] int getNumShells() const { return numShells; }

        [[nodiscard]] std::string present() const
        {
            using namespace symbols;
            //                   +---------------+
            //                   |         35.45 | <- Atomic Mass/u
            // Atomic Number ->  | 17            |
            //                   |       Cl      | <- Symbol
            //                   |    Chlorine   | <- Name
            //   Group Block ->  |     Halogen   |
            //                   +---------------+
            // Other properties
            // +------------------------+----------------------+
            // | Electron Configuration | [Ne] 3s2 3p5         |
            // +------------------------+----------------------+
            // ...
            prettyPrint::ConsoleOutput output(7, 53);

            int i = 20;
            output.write(BoxDrawing::TOP_LEFT_CORNER, { .x = 19, .y = 0 });
            for (; i < 20 + 15; i++)
                output.write(BoxDrawing::HORIZONTAL, { .x = i, .y = 0 });
            output.write(BoxDrawing::TOP_RIGHT_CORNER, { .x = i, .y = 0 });

            i = 20;
            output.write(BoxDrawing::BOTTOM_LEFT_CORNER, { .x = 19, .y = 6 });
            for (; i < 20 + 15; i++)
                output.write(BoxDrawing::HORIZONTAL, { .x = i, .y = 6 });
            output.write(BoxDrawing::BOTTOM_RIGHT_CORNER, { .x = i, .y = 6 });

            for (int j = 1; j < 6; j++)
            {
                output.write(BoxDrawing::VERTICAL, { .x = 19, .y = j });
                output.write(BoxDrawing::VERTICAL, { .x = 35, .y = j });
            }

            // Write Atomic Mass
            output.write(numUtils::roundOff(std::to_string(atomicMass), 3),
                         { .x = 35, .y = 1 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::RIGHT);
            output.write("<- Atomic Mass/u", { .x = 37, .y = 1 });

            // Write Atomic Number
            output.write("Atomic Number ->",
                         { .x = 19, .y = 2 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::RIGHT);
            output.write(std::to_string(atomicNumber), { .x = 21, .y = 2 });

            // Write Symbol
            output.write(symbol,
                         { .x = 27, .y = 3 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::LEFT);
            output.write("<- Symbol", { .x = 37, .y = 3 });

            // Write Name
            output.write(name,
                         { .x = 27, .y = 4 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::CENTER);
            output.write("<- Name", { .x = 37, .y = 4 });

            // Write Group Block
            output.write(groupBlk,
                         { .x = 27, .y = 5 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::CENTER);
            output.write("Group Block ->",
                         { .x = 19, .y = 5 },
                         false,
                         utils::colors::keepOriginal,
                         prettyPrint::HorizontalAlignment::RIGHT);
            return output.asString();
        }
    };

    class Atom
    {
        Element elem;
        int protons = elem.atomicNumber;
        int neutrons = -1;
        int electrons = elem.atomicNumber;

    public:
        Atom(const Element& elem, int neutrons = -1);

        [[nodiscard]] std::string present();
    };

    struct Ion : private Atom
    {
        Ion(const Element& elem, int charge, int neutrons = -1);
    };
} // namespace steppable::chem
