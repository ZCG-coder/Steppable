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

#pragma once

#include "steppable/number.hpp"
#include "stpSqlite.hpp"

#include <array>
#include <string>
#include <vector>

namespace steppable::chem
{
    class Subshell
    {
        Number order;
        char type;
        Number electrons;

        friend class Element;

    public:
        [[nodiscard]] std::string present() const { return order.present() + type + electrons.present(); }

        [[nodiscard]] Number getOrder() const { return order; }
        [[nodiscard]] char getType() const { return type; }
        [[nodiscard]] Number getElectrons() const { return electrons; }
    };

    class Element : sqlite::STP_DataConnectorBase
    {
        friend class Atom;

        Number atomicNumber;
        std::string symbol;
        std::string name;
        Number atomicMass;
        std::array<char, 6> cpkCol = {};
        std::vector<Subshell> electronConf;
        Number electroNeg;
        Number atomicRadius;
        Number ionizaEnergy;
        Number electronAff;
        std::string oxidStates;
        std::string stdState;
        Number meltPtK;
        Number boilPtK;
        Number density;
        std::string groupBlk;
        int yearDiscover = 0;
        bool predicted = false;
        std::vector<Number> electronShells;
        Number numShells;

    public:
        void initializeFromStmt(SQLite::Statement stmt);
        Element(int atomicNumber);

        Element(const std::string& symbol);

        [[nodiscard]] Number getAtomicNumber() const { return atomicNumber; }
        [[nodiscard]] std::string getSymbol() const { return symbol; }
        [[nodiscard]] std::string getName() const { return name; }
        [[nodiscard]] Number getAtomicMass() const { return atomicMass; }
        [[nodiscard]] std::array<char, 6> getCpkCol() const { return cpkCol; }
        [[nodiscard]] std::vector<Subshell> getElectronConf() const { return electronConf; }
        [[nodiscard]] Number getElectroNeg() const { return electroNeg; }
        [[nodiscard]] Number getAtomicRadius() const { return atomicRadius; }
        [[nodiscard]] Number getIonizaEnergy() const { return ionizaEnergy; }
        [[nodiscard]] Number getElectronAff() const { return electronAff; }
        [[nodiscard]] std::string getOxidStates() const { return oxidStates; }
        [[nodiscard]] std::string getStdState() const { return stdState; }
        [[nodiscard]] Number getMeltPtK() const { return meltPtK; }
        [[nodiscard]] Number getBoilPtK() const { return boilPtK; }
        [[nodiscard]] Number getDensity() const { return density; }
        [[nodiscard]] std::string getGroupBlk() const { return groupBlk; }
        [[nodiscard]] int getYearDiscover() const { return yearDiscover; }
        [[nodiscard]] bool getPredicted() const { return predicted; }
        [[nodiscard]] std::vector<Number> getElectronShel() const { return electronShells; }
        [[nodiscard]] Number getNumShells() const { return numShells; }

        [[nodiscard]] std::string present() const;
    };

    class Atom
    {
        Element elem;
        Number protons = elem.atomicNumber;
        Number neutrons = -1;
        Number electrons = elem.atomicNumber;

    public:
        Atom(const Element& elem, int neutrons = -1);

        [[nodiscard]] std::string present();
    };
} // namespace steppable::chem
