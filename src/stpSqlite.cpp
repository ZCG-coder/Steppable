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

#include <SQLiteCpp/SQLiteCpp.h>

namespace steppable::sqlite
{
    SQLite::Statement STP_DataConnectorBase::createStmt(const std::string& query) const
    {
        SQLite::Statement stmt(db, query);
        return stmt;
    }

    DataRows STP_DataConnectorBase::getRowsForStmt(SQLite::Statement& stmt)
    {
        DataRows rows;

        while (stmt.executeStep())
        {
            std::vector<SQLite::Column> row;
            for (int i = 0; i < stmt.getColumnCount(); i++)
                row.emplace_back(stmt.getColumn(i));

            rows.emplace_back(row);
        }

        return rows;
    }
} // namespace steppable::sqlite