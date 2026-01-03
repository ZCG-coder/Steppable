#include "stpSqlite.hpp"

#include "output.hpp"

#include <optional>
#include <sqlite3.h>
#include <string>

using namespace std::literals;

namespace steppable::sqlite
{
    namespace
    {
        const void* getColValue(sqlite3_stmt* stmt, const int colIdx)
        {
            const int colType = sqlite3_column_type(stmt, colIdx);

            const void* result = nullptr;

            switch (colType)
            {
            case SQLITE_INTEGER:
            {
                const long long data = sqlite3_column_int64(stmt, colIdx);
                result = &data;
                break;
            }

            case SQLITE_FLOAT:
            {
                const double data = sqlite3_column_double(stmt, colIdx);
                result = &data;
                break;
            }

            case SQLITE_TEXT:
            {
                const unsigned char* data = sqlite3_column_text(stmt, colIdx);
                result = data;
                break;
            }
            case SQLITE_BLOB:
            {
                const void* data = sqlite3_column_blob(stmt, colIdx);
                result = data;
                break;
            }
            default:
            {
                output::error("getColValue"s, "Cannot cast column value to C++ type"s);
                break;
            }
            }

            return result;
        }
    } // namespace

    bool STP_Sqlite::checkSelfSanity() const
    {
        if (not hasConn())
        {
            output::error("STP_SQLite::checkSelfSanity"s, "Database connection not established yet."s);
            return true;
        }
        return false;
    }

    STP_Sqlite::STP_Sqlite(const std::filesystem::path& path)
    {
        if (sqlite3_open(path.string().c_str(), &databaseConn) != 0)
        {
            output::error("STP_SQLite"s, "Cannot open the DB file -- is it there?"s);
            return;
        }
    }

    STP_Sqlite::~STP_Sqlite()
    {
        if (checkSelfSanity())
            return;

        selectDone();
        sqlite3_close(databaseConn);
    }

    std::optional<std::vector<STP_SqliteRow>> STP_Sqlite::select(const std::string& query)
    {
        if (checkSelfSanity())
            return std::nullopt;

        sqlite3_stmt* stmt;

        // Prepare statement
        if (sqlite3_prepare_v2(databaseConn, query.c_str(), query.length(), &stmt, nullptr) != 0)
        {
            output::error("STP_Sqlite::select"s, "Cannot prepare query statement"s);
            output::info("STP_Sqlite::select"s, std::string(sqlite3_errmsg(databaseConn)));
            return std::nullopt;
        }

        // Step through results
        std::vector<STP_SqliteRow> result;

        int stepResult = sqlite3_step(stmt);

        if (stepResult == SQLITE_NOTFOUND)
        {
            output::error("STP_Sqlite::select"s, "Cannot find result with query."s);
            output::info("STP_Sqlite::select"s, std::string(sqlite3_errmsg(databaseConn)));
            return std::nullopt;
        }

        while (stepResult == SQLITE_ROW)
        {
            // Encounter ROW
            const int columns = sqlite3_column_count(stmt);

            std::vector<const void*> data;

            for (int colIdx = 0; colIdx < columns; colIdx++)
            {
                const void* colValue = getColValue(stmt, colIdx);
                data.emplace_back(colValue);
            }

            STP_SqliteRow row{ .data = data };
            result.emplace_back(row);

            stepResult = sqlite3_step(stmt);
        }

        databaseStmt = stmt;

        return result;
    }

    void STP_Sqlite::selectDone()
    {
        if (databaseStmt != nullptr)
        {
            sqlite3_finalize(databaseStmt);
            databaseStmt = nullptr;
        }
    }

    bool STP_Sqlite::hasConn() const { return databaseConn != nullptr; }
} // namespace steppable::sqlite