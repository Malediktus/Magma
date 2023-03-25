#include <Magma/Renderer/RenderCommand.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Renderer/IndexBuffer.h>

namespace Magma
{
    std::shared_ptr<RenderingAPI> RenderCommand::m_RenderingAPI;
    std::shared_ptr<Shader> RenderCommand::m_BaseShader;
    std::shared_ptr<Shader> RenderCommand::m_TextureShader;
    std::unique_ptr<Camera> RenderCommand::m_Camera;

    void RenderCommand::Init(Window *window)
    {
        m_RenderingAPI = RenderingAPICreate(window);
        m_BaseShader = ShaderCreate("assets/OpenGL/Base.vert", "assets/OpenGL/Base.frag");
        m_TextureShader = ShaderCreate("assets/OpenGL/Texture.vert", "assets/OpenGL/Texture.frag");
        m_Camera = std::unique_ptr<Camera>(new FPSCamera(90.0f, window->GetWidth(), window->GetHeight()));
        m_Camera->Translate(glm::vec3(0.0f, 0.0f, 2.0f));
        EventDispatcher::Subscribe<WindowResizeEvent>(OnReisze);
    }

    void RenderCommand::Shutdown()
    {
        m_TextureShader.reset();
        m_BaseShader.reset();
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

    void RenderCommand::DrawIndexed(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform, const bool useTexture)
    {
        FPSCamera* fpsCam = (FPSCamera*)m_Camera.get();
        if (Input::GetKey(KeyCode::W))
            fpsCam->MoveFront(0.2f);
        else if (Input::GetKey(KeyCode::S))
            fpsCam->MoveFront(-0.2f);
        else if (Input::GetKey(KeyCode::A))
            fpsCam->MoveSideways(0.2f);
        else if (Input::GetKey(KeyCode::D))
            fpsCam->MoveSideways(-0.2f);
        
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBufferCreate(vertices);
        std::shared_ptr<IndexBuffer> indexBuffer = IndexBufferCreate(indices);
        glm::mat modelViewProj = transform * m_Camera->GetViewProj();
        if (useTexture)
        {
            m_TextureShader->Bind();
            m_TextureShader->UploadInt("TextureId", 0);
            m_TextureShader->UploadMat4("uModelViewProj", modelViewProj);
        }
        else
        {
            m_BaseShader->Bind();
            m_BaseShader->UploadMat4("uModelViewProj", modelViewProj);
        }
        vertexBuffer->Bind();
        indexBuffer->Bind();
        m_RenderingAPI->DrawIndexed(indexBuffer->Size(), false);
    }

    void RenderCommand::DrawIndexedWireframe(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform, const bool useTexture)
    {
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBufferCreate(vertices);
        std::shared_ptr<IndexBuffer> indexBuffer = IndexBufferCreate(indices);
        glm::mat modelViewProj = transform * m_Camera->GetViewProj();
        if (useTexture)
        {
            m_TextureShader->Bind();
            m_TextureShader->UploadInt("TextureId", 0);
            m_TextureShader->UploadMat4("uModelViewProj", modelViewProj);
        }
        else
        {
            m_BaseShader->Bind();
            m_BaseShader->UploadMat4("uModelViewProj", modelViewProj);
        }
        vertexBuffer->Bind();
        indexBuffer->Bind();
        m_RenderingAPI->DrawIndexed(indexBuffer->Size(), true);
    }

    void RenderCommand::OnReisze(const Event &e)
    {
        const WindowResizeEvent &resizeEvent = static_cast<const WindowResizeEvent&>(e);
        m_Camera->UpdateAspectRation(resizeEvent.GetWidth(), resizeEvent.GetHeight());
    }
}
