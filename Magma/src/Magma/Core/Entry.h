#pragma once

#include <memory>
#include <Magma/Core/Application.h>

extern std::shared_ptr<Magma::Application> Magma::CreateApplication();

int main(void)
{
    std::shared_ptr<Magma::Application> app = Magma::CreateApplication();
    app->Run();
    
    return 0;
}
