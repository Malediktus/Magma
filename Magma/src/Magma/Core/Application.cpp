#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>

namespace Magma
{
    void Application::Run()
    {
        EASY_FUNCTION(profiler::colors::Red);
        Logger::Init();
        OnInit();
        while (mRunning)
            ;
        OnShutdown();
    }
}