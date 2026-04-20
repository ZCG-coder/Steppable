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

#include "types/chem.hpp"

#include "SQLiteCpp/SQLiteCpp.h"
#include "output.hpp"
#include "platform.hpp"
#include "stpSqlite.hpp"
#include "util.hpp"

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <string>
#include <vector>

using namespace std::literals;

namespace steppable::chem
{
    void Element::initializeFromStmt(SQLite::Statement stmt)
    {
        auto rows = getRowsForStmt<20>(stmt);

        const auto& row = rows.front();
        if (rows.empty())
        {
            output::error("Element::initializeFromStmt"s, "No matching element found for statement."s);
            utils::programSafeExit(1);
        }

        const auto& [_atomicNumber,
                     _symbol,
                     _name,
                     _atomicMass,
                     _cpkCol,
                     _electronConf,
                     _electroNeg,
                     _atomicRadius,
                     _ionizaEnergy,
                     _electronAff,
                     _oxidStates,
                     _stdState,
                     _meltPtK,
                     _boilPtK,
                     _density,
                     _groupBlk,
                     _yearDiscover,
                     _predicted,
                     _electronShells,
                     _numShells] = row;
        this->atomicNumber = _atomicNumber;
        this->symbol = _symbol;
        this->name = _name;
        this->atomicMass = _atomicMass;
        this->electroNeg = _electroNeg;
        this->atomicRadius = _atomicRadius;
        this->ionizaEnergy = _ionizaEnergy;
        this->electronAff = _electronAff;
        this->stdState = _stdState;
        this->meltPtK = _meltPtK;
        this->boilPtK = _boilPtK;
        this->density = _density;
        this->groupBlk = _groupBlk;
        this->yearDiscover = std::stoi(_yearDiscover);
        this->predicted = _predicted == "1";
        this->numShells = _numShells;

        // Electron shells -> shells vector
        this->electronConf.clear();
        this->electronShells.clear();
        std::vector electronShellsVec = stringUtils::split(_electronShells, ',');
        std::ranges::transform(electronShellsVec,
                               std::back_inserter(this->electronShells),
                               [](const std::string& i) -> int { return std::stoi(i); });

        // Electron configuration -> subshells
        std::vector subshells = stringUtils::split(_electronConf, ',');
        for (const auto& subshell : subshells)
        {
            Subshell currentSubshell{};
            size_t i = 0;
            std::string order;
            for (;; i++)
                if ('0' <= subshell.at(i) && subshell.at(i) <= '9')
                    order += subshell.at(i);
                else
                    break;
            currentSubshell.order = order;
            currentSubshell.type = subshell[++i];

            std::string electronCount;
            for (;; i++)
                if (('0' <= subshell[i]) && (subshell[i] <= '9'))
                    electronCount += subshell[i];
                else
                    break;

            currentSubshell.electrons = electronCount;

            this->electronConf.emplace_back(currentSubshell);
        }

        // CPK color
        this->cpkCol = {
            _cpkCol[0], _cpkCol[1], _cpkCol[2], _cpkCol[3], _cpkCol[4], _cpkCol[5],
        };
    }

    Element::Element(const int atomicNumber) :
        STP_DataConnectorBase(utils::getResDirectory() / "chem" / "pd_tbl.db"), atomicNumber(atomicNumber)
    {
        try
        {
            auto stmt = createStmt("SELECT * FROM Elements WHERE AtomicNumber = ?");
            stmt.bind(1, atomicNumber);
            initializeFromStmt(std::move(stmt));
        }
        catch (const std::exception&)
        {
            output::error("Element"s, "An error occurred. ({0})"s, { std::to_string(getDb().getErrorCode()) });
            output::info("Element"s, std::string(getDb().getErrorMsg()));
        }
    }

    Element::Element(const std::string& symbol) : STP_DataConnectorBase(utils::getResDirectory() / "chem" / "pd_tbl.db")
    {
        try
        {
            auto stmt = createStmt("SELECT * FROM Elements WHERE Symbol = ?");
            stmt.bind(1, symbol);
            initializeFromStmt(std::move(stmt));
        }
        catch (const std::exception&)
        {
            output::error("Element"s, "An error occurred. ({0})"s, { std::to_string(getDb().getErrorCode()) });
            output::info("Element"s, std::string(getDb().getErrorMsg()));
        }
    }

    std::string Element::present() const
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
        prettyPrint::ConsoleOutput output(8, 100);

        constexpr int leftpad = 20;
        constexpr int width = 19;
        constexpr int height = 7;

        int i = leftpad;
        for (; i < leftpad + width; i++)
            output.write(BoxDrawing::HORIZONTAL, { .x = i, .y = 0 });
        output.write(BoxDrawing::TOP_LEFT_CORNER, { .x = leftpad, .y = 0 });
        output.write(BoxDrawing::TOP_RIGHT_CORNER, { .x = i, .y = 0 });

        i = leftpad;
        for (; i < leftpad + width; i++)
            output.write(BoxDrawing::HORIZONTAL, { .x = i, .y = height });
        output.write(BoxDrawing::BOTTOM_LEFT_CORNER, { .x = leftpad, .y = height });
        output.write(BoxDrawing::BOTTOM_RIGHT_CORNER, { .x = i, .y = height });

        for (int j = 1; j < height; j++)
        {
            output.write(BoxDrawing::VERTICAL, { .x = leftpad, .y = j });
            output.write(BoxDrawing::VERTICAL, { .x = leftpad + width, .y = j });
        }

        // Write Atomic Mass
        output.write(numUtils::roundOff(atomicMass.present(), 3),
                     { .x = leftpad + width - 2, .y = 1 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::RIGHT);
        output.write("<- Atomic Mass/u", { .x = leftpad + width + 2, .y = 1 });

        // Write Atomic Number
        output.write("Atomic Number ->",
                     { .x = leftpad - 2, .y = 2 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::RIGHT);
        output.write(atomicNumber.present(), { .x = leftpad + 2, .y = 2 });

        // Write Symbol
        output.write(symbol,
                     { .x = leftpad + (width / 2), .y = 3 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::LEFT);
        output.write("<- Symbol", { .x = leftpad + width + 2, .y = 3 });

        // Write Name
        output.write(name,
                     { .x = leftpad + (width / 2), .y = 4 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::CENTER);
        output.write("<- Name", { .x = leftpad + width + 2, .y = 4 });

        // Write Group Block
        output.write(prettyPrint::wrapString(groupBlk, width - 4, prettyPrint::WrappingOptions::BREAK),
                     { .x = leftpad + (width / 2), .y = 5 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::CENTER);
        output.write("Group Block\n->",
                     { .x = leftpad - 2, .y = 5 },
                     false,
                     utils::colors::keepOriginal,
                     prettyPrint::HorizontalAlignment::RIGHT);
        return output.asString();
    }
} // namespace steppable::chem

#ifndef NO_MAIN
int main()
{
    [[maybe_unused]] steppable::utils::Utf8CodePage utf8;

    using namespace steppable::sqlite;
    std::cout << steppable::chem::Element("Fr").present() << "\n";
}
#endif
