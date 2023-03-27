#include <Magma/pch.h>
#include <Magma/Renderer/Buffer.h>
#include <Magma/Renderer/Renderer.h>
#include <Magma/Platform/OpenGL/OpenGLBuffer.h>

using namespace Magma;

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:     MG_ASSERT_MSG(false, "RenderingAPI::None is invalid!"); return std::shared_ptr<VertexBuffer>();
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        default:                    MG_ASSERT_MSG(false, "Unknown RenderingAPI!"); return std::shared_ptr<VertexBuffer>();
    }
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:     MG_ASSERT_MSG(false, "RenderingAPI::None is invalid!"); return std::shared_ptr<IndexBuffer>();
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLIndexBuffer>(indices, size);
        default:                    MG_ASSERT_MSG(false, "Unknown RenderingAPI!"); return std::shared_ptr<IndexBuffer>();
    }
}
