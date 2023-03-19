#pragma once

#include <Magma/pch.h>

namespace Magma
{
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual const int &GetWidth() = 0;
        virtual const int &GetHeight() = 0;
        virtual const std::string &GetTitle() const = 0;

        virtual void *GetWindowEventHandle() const = 0;
        virtual std::vector<const char *> GetVulkanExtensions() const = 0;

        virtual void Update() = 0;
        virtual void Draw() = 0;
    };

    std::shared_ptr<Window> WindowCreate(const char *title, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
}