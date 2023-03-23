#include <Magma/Renderer/RenderCommand.h>

namespace Magma
{
    std::shared_ptr<RenderingAPI> RenderCommand::m_RenderingAPI;
    std::shared_ptr<VertexBuffer> RenderCommand::m_VertexBuffer;
    std::shared_ptr<IndexBuffer> RenderCommand::m_IndexBuffer;

    void RenderCommand::Init(const Window *window)
    {
        m_RenderingAPI = RenderingAPICreate(window);
        m_VertexBuffer = VertexBufferCreate();
        m_IndexBuffer = IndexBufferCreate();
    }

    void RenderCommand::Clear(glm::vec4 color)
    {
        m_RenderingAPI->Clear();
    }

    void RenderCommand::NewFrame()
    {
        m_VertexBuffer->Reset();
        m_IndexBuffer->Reset();
    }

    void RenderCommand::Submit(Mesh mesh, glm::mat4 transform)
    {
    }

    void RenderCommand::DrawIndexed()
    {
        m_RenderingAPI->DrawIndex(m_VertexBuffer.get(), m_IndexBuffer.get(), false);
    }

    void RenderCommand::DrawIndexedWireframe()
    {
        m_RenderingAPI->DrawIndex(m_VertexBuffer.get(), m_IndexBuffer.get(), true);
    }
}