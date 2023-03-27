#pragma once

#include <Magma/Renderer/RenderCommand.h>
#include <Magma/Renderer/RendererAPI.h>

namespace Magma
{
class Renderer
{
public:
    static void BeginScene();
    static void EndScene();
    
    static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    
    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};
}
