#pragma once

#include <Magma/Core/Application.h>
#include <easy/profiler.h>

extern Magma::Application* Magma::CreateApplication();

int main(void)
{
    EASY_PROFILER_ENABLE;

    Magma::Application* app = Magma::CreateApplication();
    app->Run();

    profiler::dumpBlocksToFile("Magma.prof");

    return 0;
}