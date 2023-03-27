#include <Magma/pch.h>
#include <Magma/Renderer/VertexArray.h>
#include <Magma/Renderer/Renderer.h>
#include <Magma/Platform/OpenGL/OpenGLVertexArray.h>

using namespace Magma;

std::shared_ptr<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:     MG_ASSERT_MSG(false, "RendererAPI::API::None is invalid!"); return std::shared_ptr<VertexArray>();
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLVertexArray>();
        default:                         MG_ASSERT_MSG(false, "Unknown RenderingAPI!"); return std::shared_ptr<VertexArray>();
    }
}
