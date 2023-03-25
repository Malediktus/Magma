#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Platform/OpenGL/OpenGLVertexBuffer.h>
#include <Magma/Platform/Vulkan/VulkanVertexBuffer.h>

namespace Magma
{
    std::shared_ptr<VertexBuffer> VertexBufferCreate(const std::vector<RawVertex> &vertices)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices));
        case RenderingAPIType::Vulkan:
            return std::shared_ptr<VertexBuffer>(new VulkanVertexBuffer(vertices));
        default:
            MG_ASSERT_NO_MSG(false);
        }
    }
}