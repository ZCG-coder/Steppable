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

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "output.hpp"
#include "platform.hpp"

#include <filesystem>
#include <type_traits>
#include <vector>

namespace steppable::sqlite
{
    using DataRows = std::vector<std::vector<std::string>>;

    class STP_DataConnectorBase
    {
        SQLite::Database db;

        template<typename... ColumnT, std::size_t... Is>
        std::tuple<ColumnT...> rowToTuple(const std::vector<SQLite::Column>& row, std::index_sequence<Is...> /*unused*/)
        {
            return std::make_tuple(static_cast<ColumnT>(row[Is])...);
        }

    public:
        explicit STP_DataConnectorBase(const std::filesystem::path& dbPath);

        [[nodiscard]] SQLite::Statement createStmt(const std::string& query) const;

        template<typename... ColumnT>
        std::vector<std::tuple<ColumnT...>> getRowsForStmt(SQLite::Statement& stmt)
        {
            std::vector<std::tuple<ColumnT...>> rows;

            while (stmt.executeStep())
            {
                std::vector<SQLite::Column> row;
                row.reserve(stmt.getColumnCount());
                for (int i = 0; i < stmt.getColumnCount(); ++i)
                    row.emplace_back(stmt.getColumn(i));

                rows.emplace_back(rowToTuple<ColumnT...>(row, std::index_sequence_for<ColumnT...>()));
            }

            return rows;
        }

        template<typename ColumnT>
        static std::vector<std::remove_cvref_t<ColumnT>> getColForStmt(SQLite::Statement& stmt,
                                                                       const std::string& colName);

        template<typename ColumnT>
        static std::vector<std::remove_cvref_t<ColumnT>> getColForStmt(SQLite::Statement& stmt, const int& colIdx);

        SQLite::Database& getDb() { return db; }
    };

    template<typename ColumnT>
    std::vector<std::remove_cvref_t<ColumnT>> STP_DataConnectorBase::getColForStmt(SQLite::Statement& stmt,
                                                                                   const std::string& colName)
    {
        using ReturnT = std::remove_cvref_t<ColumnT>;

        std::vector<ReturnT> res;

        while (stmt.executeStep())
        {
            ColumnT colValue = stmt.getColumn(colName.c_str());
            res.emplace_back(colValue);
        }

        return res;
    }

    template<typename ColumnT>
    std::vector<std::remove_cvref_t<ColumnT>> STP_DataConnectorBase::getColForStmt(SQLite::Statement& stmt,
                                                                                   const int& colIdx)
    {
        using ReturnT = std::remove_cvref_t<ColumnT>;

        std::vector<ReturnT> res;

        while (stmt.executeStep())
        {
            ColumnT colValue = stmt.getColumn(colIdx);
            res.emplace_back(colValue);
        }

        return res;
    }
} // namespace steppable::sqlite