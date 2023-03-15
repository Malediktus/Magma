#pragma once

#include <Magma/pch.h>
#include <spdlog/spdlog.h>

namespace Magma
{
    class Logger
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return m_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return m_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_CoreLogger;
        static std::shared_ptr<spdlog::logger> m_ClientLogger;
    };
}

#define LOG_CORE_TRACE(...) ::Magma::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::Magma::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::Magma::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Magma::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) ::Magma::Logger::GetCoreLogger()->fatal(__VA_ARGS__)

#define LOG_TRACE(...) ::Magma::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Magma::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Magma::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Magma::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) ::Magma::Logger::GetClientLogger()->fatal(__VA_ARGS__)