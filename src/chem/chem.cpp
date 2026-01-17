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

#include "SQLiteCpp/Column.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "output.hpp"
#include "platform.hpp"
#include "stpSqlite.hpp"
#include "util.hpp"

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std::literals;

namespace steppable::chem
{
    Element::Element(const int atomicNumber) :
        sqlite::STP_DataConnectorBase(steppable::utils::getResDirectory() / "chem" / "pd_tbl.db"),
        atomicNumber(atomicNumber)
    {
        try
        {
            auto stmt = createStmt("SELECT * FROM Elements WHERE AtomicNumber = ?");
            stmt.bind(1, atomicNumber);
            auto rows = getRowsForStmt<20>(stmt);

            const auto& row = rows.front();

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
        catch (const std::exception& e)
        {
            output::error("Element"s, "An error occurred. ({0})"s, { std::to_string(getDb().getErrorCode()) });
            output::info("Element"s, std::string(getDb().getErrorMsg()));
        }
    }
} // namespace steppable::chem

#ifndef NO_MAIN
int main()
{
    steppable::utils::Utf8CodePage utf8;

    using namespace steppable::sqlite;
    steppable::chem::Element hydrogen(1);

    std::cout << hydrogen.present() << "\n";
}
#endif
