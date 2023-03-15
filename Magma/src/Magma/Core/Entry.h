#pragma once

#include <Magma/Core/Application.h>
#ifdef _DEBUG
#include <easy/profiler.h>
#endif

extern Magma::Application* Magma::CreateApplication();

int main(void)
{
    #ifdef _DEBUG
    EASY_PROFILER_ENABLE;
    #endif

    Magma::Application* app = Magma::CreateApplication();
    app->Run();

    #ifdef _DEBUG
    profiler::dumpBlocksToFile("Magma.prof");
    #endif

    return 0;
}