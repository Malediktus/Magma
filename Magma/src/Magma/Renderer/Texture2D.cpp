#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/Texture2D.h>
#include <Magma/Platform/OpenGL/OpenGLTexture2D.h>

namespace Magma
{
    std::shared_ptr<Texture2D> Texture2DCreate(const std::string &filename)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<Texture2D>(new OpenGLTexture2D(filename));
        }
    }
}