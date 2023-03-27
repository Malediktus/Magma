#include <Magma/pch.h>
#include <Magma/Renderer/RendererAPI.h>
#include <Magma/Renderer/Renderer.h>
#include <Magma/Platform/OpenGL/OpenGLRendererAPI.h>

using namespace Magma;

auto RendererAPI::m_API = RendererAPI::API::OpenGL;

std::shared_ptr<RendererAPI> RendererAPI::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:     MG_ASSERT_MSG(false, "RendererAPI::API::None is invalid!"); return std::shared_ptr<RendererAPI>();
        case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLRendererAPI>();
        default:                         MG_ASSERT_MSG(false, "Unknown RenderingAPI!"); return std::shared_ptr<RendererAPI>();
    }
}
