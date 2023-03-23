#pragma once

#include <Magma/Core/Application.h>

extern Magma::Application* Magma::CreateApplication();

int main(void)
{
    Magma::Application* app = Magma::CreateApplication();
    app->Run();

    return 0;
}