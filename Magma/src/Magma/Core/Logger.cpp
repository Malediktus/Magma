#include <Magma/pch.h>
#include <Magma/Core/Logger.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Magma
{
    std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::m_ClientLogger;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_CoreLogger = spdlog::stdout_color_mt("MAGMA");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = spdlog::stdout_color_mt("APP");
        m_ClientLogger->set_level(spdlog::level::trace);
    }
}

void report_assertion_failure(const char *expression, const char *message, const char *file, int line)
{
    LOG_CORE_FATAL("Assertion failure: {}, '{}', in File {}, Line {}", expression, message, file, line);
}