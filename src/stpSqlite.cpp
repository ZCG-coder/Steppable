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

#include "stpSqlite.hpp"

#include "SQLiteCpp/Column.h"

#include <SQLiteCpp/SQLiteCpp.h>

namespace steppable::sqlite
{
    STP_DataConnectorBase::STP_DataConnectorBase(const std::filesystem::path& dbPath) : db(SQLite::Database(":memory:"))
    {
        using namespace std::literals;

        std::cout << dbPath << "\n";

        if (not std::filesystem::is_regular_file(dbPath))
        {
            output::error("STP_DataConnectorBase"s, "No such database file {0}"s, { dbPath.string() });
            utils::programSafeExit(1);
        }
        db = SQLite::Database(dbPath);
    }
    SQLite::Statement STP_DataConnectorBase::createStmt(const std::string& query) const
    {
        SQLite::Statement stmt(db, query);
        return stmt;
    }
} // namespace steppable::sqlite