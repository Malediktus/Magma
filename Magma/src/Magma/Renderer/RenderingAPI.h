#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>

namespace Magma
{
    class RenderingAPI
    {
    public:
        virtual ~RenderingAPI() = default;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;
        
        virtual void BeginGui() = 0;
        virtual void EndGui() = 0;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window);
}
