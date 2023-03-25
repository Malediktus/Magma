#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/Texture2D.h>
#include <Magma/Platform/OpenGL/OpenGLTexture2D.h>
#include <Magma/Platform/Vulkan/VulkanTexture2D.h>

namespace Magma
{
    std::shared_ptr<Texture2D> Texture2DCreate(const std::string &filename)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<Texture2D>(new OpenGLTexture2D(filename));
        case RenderingAPIType::Vulkan:
            return std::shared_ptr<Texture2D>(new VulkanTexture2D(filename));
        default:
            MG_ASSERT_NO_MSG(false);
            return std::shared_ptr<Texture2D>();
        }
    }
}