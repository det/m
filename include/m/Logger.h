#pragma once
#include "m/SpinLock.h"
#include "fmt/format.h"
#include "fmt/time.h"
#include <chrono>
#include <ctime>
#include <cstdio>
#include <memory>
#include <mutex>
#include <string>

namespace m {
    enum class LogLevel {
        debug,
        info,
        warning,
        error,
    };

    constexpr const char* levelString(LogLevel level) {
        switch (level) {
            case LogLevel::debug:   return "DEBUG";
            case LogLevel::info:    return "INFO";
            case LogLevel::warning: return "WARNING";
            case LogLevel::error:   return "ERROR";
        }
    }

    struct LogMessage {
        LogLevel level;
        const char* file;
        unsigned int line;
        std::string text;
        std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
    };

    struct LoggerInterface {
        virtual ~LoggerInterface() {}
        virtual void log(LogMessage message) = 0;
    };

    class DefaultLogger : public LoggerInterface {
    public:
        virtual void log(LogMessage message) {
            auto d = message.time.time_since_epoch();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(d - std::chrono::duration_cast<std::chrono::seconds>(d));
            auto timet = std::chrono::system_clock::to_time_t(message.time);

            auto s = fmt::format("[{:%F %T}.{:03d}] {} {}:{} {}\n",
                               *gmtime(&timet),
                               milliseconds.count(),
                               levelString(message.level),
                               message.file,
                               message.line,
                               message.text);

            auto lock = std::lock_guard(spin_lock_);

            if (message.level != LogLevel::error)
                std::fwrite(s.c_str(), 1, s.size(), stdout);
            else {
                std::fflush(stdout);
                std::fwrite(s.c_str(), 1, s.size(), stderr);
                std::fflush(stderr);
            }
        }

    private:
        SpinLock spin_lock_;
    };

    namespace detail {
        inline std::unique_ptr<LoggerInterface>& getGlobalLogger() {
            static std::unique_ptr<LoggerInterface> logger = std::make_unique<DefaultLogger>();
            return logger;
        }
    }

    inline LoggerInterface& getGlobalLogger() {
        return *detail::getGlobalLogger();
    }

    inline void setGlobalLogger(std::unique_ptr<LoggerInterface> logger) {
        detail::getGlobalLogger() = std::move(logger);
    }

    #define M_LOG(LEVEL, ...)  ::m::getGlobalLogger().log({LEVEL, __FILE__, __LINE__, fmt::format(__VA_ARGS__)})
    #define M_LOG_DEBUG(...)   M_LOG(::m::LogLevel::debug,  __VA_ARGS__)
    #define M_LOG_INFO(...)    M_LOG(::m::LogLevel::info,   __VA_ARGS__)
    #define M_LOG_WARNING(...) M_LOG(::m::LogLevel::warning,__VA_ARGS__)
    #define M_LOG_ERROR(...)   M_LOG(::m::LogLevel::error,  __VA_ARGS__)

    #define M_LOG_RATE_LIMITED(LEVEL, INTERVAL, ...)                                                                \
    do {                                                                                                            \
        static ::std::atomic<::std::chrono::steady_clock::time_point> m_log_prev_;                                  \
        auto m_log_now_ = ::std::chrono::steady_clock::now();                                                       \
        auto m_log_last_ = m_log_prev_.load(::std::memory_order_acquire);                                           \
        if (m_log_now_ - m_log_last_ >= (INTERVAL) && m_log_prev_.compare_exchange_strong(m_log_last_, m_log_now_)) \
            M_LOG(LEVEL, __VA_ARGS__);                                                                              \
    } while (false)

    #define M_LOG_RATE_LIMITED_DEBUG(INTERVAL, ...)   M_LOG_RATE_LIMITED(::m::LogLevel::debug,   INTERVAL, __VA_ARGS__)
    #define M_LOG_RATE_LIMITED_INFO(INTERVAL, ...)    M_LOG_RATE_LIMITED(::m::LogLevel::info,    INTERVAL, __VA_ARGS__)
    #define M_LOG_RATE_LIMITED_WARNING(INTERVAL, ...) M_LOG_RATE_LIMITED(::m::LogLevel::warning, INTERVAL, __VA_ARGS__)
    #define M_LOG_RATE_LIMITED_ERROR(INTERVAL, ...)   M_LOG_RATE_LIMITED(::m::LogLevel::error,   INTERVAL, __VA_ARGS__)
}
