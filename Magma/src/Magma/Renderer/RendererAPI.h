#pragma once

#include <glm/glm.hpp>
#include <Magma/Renderer/VertexArray.h>

namespace Magma
{
class RendererAPI
{
public:
    enum class API
    {
        None = 0,
        OpenGL = 1
    };
    
    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;
    
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
    
    inline static RendererAPI::API GetAPI() { return m_API; }
    
    static std::shared_ptr<RendererAPI> Create();
    
private:
    static API m_API;
};
}
