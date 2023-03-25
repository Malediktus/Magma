#pragma once

#include <Magma/pch.h>

namespace Magma
{
class Window
{
public:
    virtual ~Window() = default;
    
    virtual const int& GetWidth() = 0;
    virtual const int& GetHeight() = 0;
    virtual const std::string& GetTitle() const = 0;
    virtual void* GetNative() const = 0;
    
    virtual void Update() = 0;
};

std::shared_ptr<Window> WindowCreate(const std::string &title, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
}
