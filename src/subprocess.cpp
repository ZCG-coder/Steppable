#include "subprocess.hpp"

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

#ifdef WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <csignal>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>
#endif

namespace steppable
{
    using std::string;

#ifdef WINDOWS
    bool Subprocess::start(const std::string& command,
                           const std::vector<std::string>& args,
                           std::istream* stdin_stream,
                           std::ostream* stdout_stream)
    {
        std::ostringstream cmdline;
        cmdline << "\"" << command << "\"";
        for (const auto& arg : args)
            cmdline << " \"" << arg << "\"";
        std::string cmd = cmdline.str();
        STARTUPINFOA si = { sizeof(STARTUPINFOA) };
        PROCESS_INFORMATION pi = {};
        HANDLE hStdInRead = nullptr, hStdInWrite = nullptr;
        HANDLE hStdOutRead = nullptr, hStdOutWrite = nullptr;
        SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
        if (stdin_stream)
        {
            if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
                return false;
            si.hStdInput = hStdInRead;
            si.dwFlags |= STARTF_USESTDHANDLES;
        }
        if (stdout_stream)
        {
            if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
                return false;
            si.hStdOutput = hStdOutWrite;
            si.dwFlags |= STARTF_USESTDHANDLES;
        }
        BOOL res = CreateProcessA(nullptr, (LPSTR)cmd.c_str(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi);
        if (!res)
        {
            if (hStdInRead)
                CloseHandle(hStdInRead);
            if (hStdInWrite)
                CloseHandle(hStdInWrite);
            if (hStdOutRead)
                CloseHandle(hStdOutRead);
            if (hStdOutWrite)
                CloseHandle(hStdOutWrite);
            return false;
        }
        processHandle = pi.hProcess;
        processId = pi.dwProcessId;
        CloseHandle(pi.hThread);
        // Write to child's stdin if provided
        if (stdin_stream && hStdInWrite)
        {
            std::string input((std::istreambuf_iterator<char>(*stdin_stream)), std::istreambuf_iterator<char>());
            DWORD written = 0;
            WriteFile(hStdInWrite, input.data(), (DWORD)input.size(), &written, nullptr);
            CloseHandle(hStdInWrite);
        }
        if (hStdInRead)
            CloseHandle(hStdInRead);
        // Read from child's stdout if provided
        if (stdout_stream && hStdOutRead)
        {
            char buffer[4096];
            DWORD read = 0;
            while (ReadFile(hStdOutRead, buffer, sizeof(buffer), &read, nullptr) && read > 0)
                stdout_stream->write(buffer, read);
            CloseHandle(hStdOutRead);
        }
        if (hStdOutWrite)
            CloseHandle(hStdOutWrite);
        return true;
    }

    bool Subprocess::is_running()
    {
        if (!processHandle)
            return false;
        DWORD status = 0;
        if (GetExitCodeProcess(processHandle, &status))
            return status == STILL_ACTIVE;
        return false;
    }

    int Subprocess::wait()
    {
        if (!processHandle)
            return -1;
        WaitForSingleObject(processHandle, INFINITE);
        DWORD exitCode = 0;
        GetExitCodeProcess(processHandle, &exitCode);
        CloseHandle(processHandle);
        processHandle = nullptr;
        return static_cast<int>(exitCode);
    }

    void Subprocess::killProc()
    {
        if (processHandle)
        {
            TerminateProcess(processHandle, 1);
            CloseHandle(processHandle);
            processHandle = nullptr;
        }
    }

    Subprocess::~Subprocess()
    {
        if (processHandle)
        {
            CloseHandle(processHandle);
            processHandle = nullptr;
        }
    }

    // Windows implementation of STP_IPC
    STP_IPC::STP_IPC(const std::string& name, size_t size, bool create) : region_size(size), shm_name(name)
    {
        DWORD flProtect = PAGE_READWRITE;
        DWORD dwAccess = FILE_MAP_ALL_ACCESS;
        hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE,
                                      nullptr,
                                      flProtect,
                                      (DWORD)(region_size >> 32),
                                      (DWORD)(region_size & 0xFFFFFFFF),
                                      shm_name.c_str());
        if (!hMapFile)
            throw std::runtime_error("Failed to create/open file mapping");
        pData = MapViewOfFile(hMapFile, dwAccess, 0, 0, region_size);
        if (!pData)
        {
            CloseHandle(hMapFile);
            throw std::runtime_error("Failed to map view of file");
        }
    }

    STP_IPC::~STP_IPC()
    {
        if (pData)
            UnmapViewOfFile(pData);
        if (hMapFile)
            CloseHandle(hMapFile);
    }

    void* STP_IPC::data() { return pData; }
    size_t STP_IPC::size() const { return region_size; }
    void STP_IPC::flush()
    {
        if (pData)
            FlushViewOfFile(pData, region_size);
    }
    // POSIX implementation of STP_IPC
    STP_IPC::STP_IPC(const std::string& name, size_t size, bool create) : region_size(size), shm_name(name)
    {
        int flags = O_RDWR;
        if (create)
            flags |= O_CREAT;
        shm_fd = shm_open(shm_name.c_str(), flags, 0666);
        if (shm_fd == -1)
            throw std::runtime_error("Failed to open shared memory");
        if (create)
        {
            if (ftruncate(shm_fd, region_size) == -1)
            {
                close(shm_fd);
                shm_unlink(shm_name.c_str());
                throw std::runtime_error("Failed to set shared memory size");
            }
        }
        pData = mmap(nullptr, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (pData == MAP_FAILED)
        {
            close(shm_fd);
            shm_unlink(shm_name.c_str());
            throw std::runtime_error("Failed to mmap shared memory");
        }
    }

    STP_IPC::~STP_IPC()
    {
        if (pData && pData != MAP_FAILED)
            munmap(pData, region_size);
        if (shm_fd != -1)
            close(shm_fd);
        // Optionally: shm_unlink(shm_name.c_str());
    }

    void* STP_IPC::data() { return pData; }
    size_t STP_IPC::size() const { return region_size; }
    void STP_IPC::flush()
    {
        if (pData && pData != MAP_FAILED)
            msync(pData, region_size, MS_SYNC);
    }
#else // POSIX
    bool Subprocess::start(const std::string& command,
                           const std::vector<std::string>& args,
                           std::istream* stdin_stream,
                           std::ostream* stdout_stream)
    {
        int in_pipe[2] = { -1, -1 };
        int out_pipe[2] = { -1, -1 };
        if (stdin_stream != nullptr)
        {
            if (pipe(in_pipe) < 0)
                return false;
        }
        if (stdout_stream != nullptr)
        {
            if (pipe(out_pipe) < 0)
            {
                if (in_pipe[0] != -1)
                {
                    close(in_pipe[0]);
                    close(in_pipe[1]);
                }
                return false;
            }
        }
        pid = fork();
        if (pid < 0)
        {
            if (in_pipe[0] != -1)
            {
                close(in_pipe[0]);
                close(in_pipe[1]);
            }
            if (out_pipe[0] != -1)
            {
                close(out_pipe[0]);
                close(out_pipe[1]);
            }
            return false;
        }
        if (pid == 0)
        {
            // Child process
            if (stdin_stream != nullptr)
            {
                dup2(in_pipe[0], STDIN_FILENO);
                close(in_pipe[0]);
                close(in_pipe[1]);
            }
            if (stdout_stream != nullptr)
            {
                dup2(out_pipe[1], STDOUT_FILENO);
                close(out_pipe[0]);
                close(out_pipe[1]);
            }
            std::vector<char*> argv;
            argv.push_back(const_cast<char*>(command.c_str())); // NOLINT(cppcoreguidelines-pro-type-const-cast)
            for (const auto& arg : args)
                argv.push_back(const_cast<char*>(arg.c_str())); // NOLINT(cppcoreguidelines-pro-type-const-cast)
            argv.push_back(nullptr);
            execvp(command.c_str(), argv.data());
            _exit(127); // If exec fails
        }
        // Parent process
        if (stdin_stream != nullptr)
        {
            close(in_pipe[0]);
            std::string input((std::istreambuf_iterator<char>(*stdin_stream)), std::istreambuf_iterator<char>());
            write(in_pipe[1], input.data(), input.size());
            close(in_pipe[1]);
        }
        if (stdout_stream != nullptr)
        {
            close(out_pipe[1]);
            char buffer[4096];
            ssize_t n = 0;
            while ((n = read(out_pipe[0], buffer, sizeof(buffer))) > 0)
                stdout_stream->write(buffer, n);
            close(out_pipe[0]);
        }
        return true;
    }

    bool Subprocess::is_running()
    {
        if (pid <= 0)
            return false;
        int status = 0;
        pid_t result = waitpid(pid, &status, WNOHANG);
        if (result == 0)
            return true; // Still running
        if (result == pid)
            pid = -1;
        return false;
    }

    int Subprocess::wait()
    {
        if (pid <= 0)
            return -1;
        int status = 0;
        waitpid(pid, &status, 0);
        pid = -1;
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        return -1;
    }

    void Subprocess::killProc()
    {
        if (pid > 0)
        {
            ::kill(pid, SIGKILL);
            waitpid(pid, nullptr, 0);
            pid = -1;
        }
    }

    Subprocess::~Subprocess()
    {
        if (pid > 0)
        {
            ::kill(pid, SIGKILL);
            waitpid(pid, nullptr, 0);
            pid = -1;
        }
    }

    STP_IPC::STP_IPC(const string& name, size_t size, bool create) : region_size(size), shm_name(name)
    {
        int flags = O_RDWR;
        if (create)
            flags |= O_CREAT;
        shm_fd = shm_open(shm_name.c_str(), flags, S_IRWXU | S_IRWXG);
        if (shm_fd == -1)
            throw std::runtime_error("Failed to open shared memory");
        if (create)
        {
            if (ftruncate(shm_fd, region_size) == -1)
            {
                close(shm_fd);
                shm_unlink(shm_name.c_str());
                throw std::runtime_error("Failed to set shared memory size");
            }
        }
        pData = mmap(nullptr, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (pData == MAP_FAILED)
        {
            close(shm_fd);
            shm_unlink(shm_name.c_str());
            throw std::runtime_error("Failed to mmap shared memory");
        }
    }

    void STP_IPC::unlink() { shm_unlink(shm_name.c_str()); }

    STP_IPC::~STP_IPC()
    {
        if ((pData != nullptr) && pData != MAP_FAILED)
            munmap(pData, region_size);
        if (shm_fd != -1)
            close(shm_fd);
    }

    void* STP_IPC::data() { return pData; }
    size_t STP_IPC::size() const { return region_size; }
    void STP_IPC::flush()
    {
        if ((pData != nullptr) && pData != MAP_FAILED)
            msync(pData, region_size, MS_SYNC);
    }
#endif
} // namespace steppable
