#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <ctime>
#include <cstdio>
#include <sstream>

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#else
  #include <unistd.h>
  #include <limits.h>
#endif

// 单例日志器：写入 程序所在目录/debugger.log
class Logger {
public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lk(mtx_);
        if (!ofs_.is_open()) return;

        // ----- 时间戳（跨平台） -----
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#if defined(_MSC_VER)
        localtime_s(&tm, &t);          // MSVC
#elif defined(__MINGW32__) || defined(__MINGW64__)
        std::tm* p = std::localtime(&t); // MinGW 用 localtime
        if (p) tm = *p;
#else
        localtime_r(&t, &tm);          // Linux/POSIX
#endif

        char timeBuf[32];
        std::snprintf(timeBuf, sizeof(timeBuf),
                      "%04d-%02d-%02d %02d:%02d:%02d",
                      tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                      tm.tm_hour, tm.tm_min, tm.tm_sec);

        ofs_ << "[" << timeBuf << "] " << msg << "\n";
        ofs_.flush();                  // 立即落盘
    }

    void close() {
        std::lock_guard<std::mutex> lk(mtx_);
        if (ofs_.is_open()) ofs_.close();
    }

private:
    Logger() {
        std::string dir = getExeDir();
        std::string logPath = dir + "/debugger.log";

        ofs_.open(logPath.c_str(), std::ios::out | std::ios::app);
        if (ofs_.is_open()) {
            ofs_ << "\n===== log start =====\n";
        }
    }

    ~Logger() {
        if (ofs_.is_open()) ofs_.close();
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 取可执行文件所在目录
    static std::string getExeDir() {
#ifdef _WIN32
        char path[MAX_PATH] = {0};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        std::string exePath(path);
#else
        char path[PATH_MAX] = {0};
        ssize_t n = readlink("/proc/self/exe", path, sizeof(path) - 1);
        std::string exePath = (n > 0) ? std::string(path, n) : ".";
#endif
        size_t pos = exePath.find_last_of("\\/");
        return (pos == std::string::npos) ? std::string(".") : exePath.substr(0, pos);
    }

    std::ofstream ofs_;
    std::mutex    mtx_;
};

// 方便使用的宏
#define LOG(msg) do { \
    std::ostringstream _oss; _oss << msg; \
    Logger::instance().log(_oss.str()); \
} while(0)

#endif // LOGGER_H
