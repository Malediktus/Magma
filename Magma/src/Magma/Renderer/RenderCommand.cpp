#include <Magma/Renderer/RenderCommand.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Renderer/IndexBuffer.h>

namespace Magma
{
    std::shared_ptr<RenderingAPI> RenderCommand::m_RenderingAPI;
    std::shared_ptr<Shader> RenderCommand::m_Shader;

    void RenderCommand::Init(Window *window)
    {
        m_RenderingAPI = RenderingAPICreate(window);
        m_Shader = ShaderCreate("assets/Base.vert", "assets/Base.frag");
    }

    void RenderCommand::Shutdown()
    {
        m_Shader.reset();
        m_RenderingAPI.reset();
    }

    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        m_RenderingAPI->SetViewport(x, y, width, height);
    }

    void RenderCommand::Clear(const glm::vec4 &color)
    {
        m_RenderingAPI->Clear(color);
    }

    void RenderCommand::DrawIndexed(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform)
    {
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBufferCreate(vertices);
        std::shared_ptr<IndexBuffer> indexBuffer = IndexBufferCreate(indices);
        m_Shader->Bind();
        m_Shader->UploadInt("TextureId", 0);
        m_Shader->UploadMat4("uModel", transform);
        vertexBuffer->Bind();
        indexBuffer->Bind();
        m_RenderingAPI->DrawIndexed(indexBuffer->Size(), false);
    }

    void RenderCommand::DrawIndexedWireframe(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform)
    {
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBufferCreate(vertices);
        std::shared_ptr<IndexBuffer> indexBuffer = IndexBufferCreate(indices);
        m_Shader->Bind();
        m_Shader->UploadInt("TextureId", 0);
        m_Shader->UploadMat4("uModel", transform);
        vertexBuffer->Bind();
        indexBuffer->Bind();
        m_RenderingAPI->DrawIndexed(indexBuffer->Size(), true);
    }
}