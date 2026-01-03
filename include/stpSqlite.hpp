#pragma once

#include <filesystem>
#include <optional>
#include <sqlite3.h>

namespace steppable::sqlite
{
    struct STP_SqliteRow
    {
        std::vector<const void*> data;

        template<typename ColT>
        ColT getValue(const int idx) const
        {
            const void* value = data[idx];

            return reinterpret_cast<ColT>(value);
        }
    };

    class STP_Sqlite // NOLINT(cppcoreguidelines-special-member-functions)
    {
        sqlite3* databaseConn = nullptr; ///< Database connection pointer.

        sqlite3_stmt* databaseStmt; ///< Statement previously executed.

        /**
         * @brief Checks if the database connection is sane, i.e., established correctly.
         * @return True if database connection is not sane. False otherwise.
         */
        [[nodiscard]] bool checkSelfSanity() const;

    public:
        /**
         * @brief Initializes a new SQLite database wrapper.
         */
        explicit STP_Sqlite(const std::filesystem::path& path);

        /**
         * @brief Destroys the instance. Deallocates memory.
         */
        ~STP_Sqlite();

        /**
         * @brief Executes a `SELECT` operation.
         *
         * @note Even though the name is `select`, you should always provide the entire `SELECT` statement.
         *
         * @param query Query to use for SELECT.
         * @return An optional vector of rows selected.
         */
        [[nodiscard]] std::optional<std::vector<STP_SqliteRow>> select(const std::string& query);

        /**
         * @brief Signals that the `SELECT` operation is done and the memory selected may be deallocated.
         *
         * @note It is crucial to call this method after processing data from `SELECT`, as it may otherwise lead to
         * memory leaks.
         */
        void selectDone();

        [[nodiscard]] bool hasConn() const;
    };
} // namespace steppable::sqlite
