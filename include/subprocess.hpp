#pragma once

#include <string>
#include <vector>

namespace steppable
{
    /**
     * @brief Cross-platform subprocess launcher and manager.
     *
     * Allows starting, waiting, killing, and checking the status of a subprocess
     * on both POSIX and Windows systems.
     */
    class Subprocess // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief Starts a new subprocess, optionally exposing a pipe for reading child's output.
         *
         * @param command The executable to run (e.g. "python3", "ls", "myapp.exe").
         * @param args The command line arguments (excluding the executable name).
         * @param stdin_stream Optional pointer to an istream to use as the child's stdin (nullptr for default).
         * @param stdout_stream Optional pointer to an ostream to use as the child's stdout (nullptr for default).
         * @return true if the process was created successfully, false otherwise.
         */
        bool start(const std::string& command,
                   const std::vector<std::string>& args,
                   std::istream* stdin_stream = nullptr,
                   std::ostream* stdout_stream = nullptr);

        /**
         * @brief Checks if the subprocess is still running.
         *
         * @return true if the process is running, false otherwise.
         */
        bool is_running();

        /**
         * @brief Waits for the subprocess to finish.
         *
         * @return The exit code of the process (or -1 on error).
         */
        int wait();

        /**
         * @brief Kills (forcibly terminates) the subprocess.
         *
         * No effect if the process is not running.
         */
        void killProc();

        /**
         * @brief Destructor. Ensures the process is cleaned up.
         *
         * Kills the process if still running and releases resources.
         */
        ~Subprocess();

    private:
#ifdef WINDOWS
        void* processHandle = nullptr; ///< Windows process handle.
        unsigned long processId = 0; ///< Windows process ID.
#else
        pid_t pid = -1; ///< POSIX process ID.
#endif
    };

    class STP_IPC // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief Create or open a shared memory region for IPC.
         * @param name Unique name for the shared memory region.
         * @param size Size of the memory region in bytes.
         * @param create If true, create a new region; otherwise, open existing.
         */
        STP_IPC(const std::string& name, size_t size, bool create = true);

        /**
         * @brief Destructor. Cleans up resources.
         */
        ~STP_IPC();

        /**
         * @brief Delete associated SHM.
         */
        void unlink();

        /**
         * @brief Get pointer to the mapped memory region.
         */
        void* data();

        /**
         * @brief Get the size of the mapped region.
         */
        [[nodiscard]] size_t size() const;

        /**
         * @brief Flush changes to the mapped region (if needed).
         */
        void flush();

    private:
        // Platform-specific handles
        void* hMapFile = nullptr; // Windows only
        int shm_fd = -1; // POSIX only
        void* pData = nullptr; // Pointer to mapped memory
        size_t region_size = 0;
        std::string shm_name;
    };
} // namespace steppable