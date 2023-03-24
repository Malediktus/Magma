#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/RenderingAPI.h>
#include <Magma/Platform/OpenGL/OpenGLRenderingAPI.h>

namespace Magma
{
    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<RenderingAPI>(new OpenGLRenderingAPI(window));
        }
    }
}