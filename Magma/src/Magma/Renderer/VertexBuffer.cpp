#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Platform/OpenGL/OpenGLVertexBuffer.h>

namespace Magma
{
    std::shared_ptr<VertexBuffer> VertexBufferCreate(const std::vector<RawVertex> &vertices)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices));
        }
    }
}