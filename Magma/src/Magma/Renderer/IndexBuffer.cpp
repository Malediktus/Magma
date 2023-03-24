#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/IndexBuffer.h>
#include <Magma/Platform/OpenGL/OpenGLIndexBuffer.h>

namespace Magma
{
    std::shared_ptr<IndexBuffer> IndexBufferCreate(const std::vector<uint32_t> &indices)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices));
        }
    }
}