#pragma once

#include <Magma/pch.h>
#include <Magma/Renderer/RendererAPI.h>
#include <Magma/Renderer/VertexArray.h>

namespace Magma
{
class RenderCommand
{
public:
    static void Init()
    {
        m_RendererAPI = RendererAPI::Create();
    }
    
    inline static void SetClearColor(const glm::vec4& color)
    {
        m_RendererAPI->SetClearColor(color);
    }
    
    inline static void Clear()
    {
        m_RendererAPI->Clear();
    }
    
    inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        m_RendererAPI->DrawIndexed(vertexArray);
    }
    
private:
    static std::shared_ptr<RendererAPI> m_RendererAPI;
};
}
