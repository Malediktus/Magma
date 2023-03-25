#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/IndexBuffer.h>
#include <Magma/Platform/OpenGL/OpenGLIndexBuffer.h>
#include <Magma/Platform/Vulkan/VulkanIndexBuffer.h>

namespace Magma
{
    std::shared_ptr<IndexBuffer> IndexBufferCreate(const std::vector<uint32_t> &indices)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices));
        case RenderingAPIType::Vulkan:
            return std::shared_ptr<IndexBuffer>(new VulkanIndexBuffer(indices));
        default:
            MG_ASSERT_NO_MSG(false);
        }
    }
}