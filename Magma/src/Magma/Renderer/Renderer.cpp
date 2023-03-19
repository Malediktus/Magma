#include <Magma/Renderer/Renderer.h>

namespace Magma
{
    std::shared_ptr<RenderingAPI> Renderer::m_RenderingAPI;

    void Renderer::Init(Window *window)
    {
        m_RenderingAPI = RenderingAPICreate(window);
    }

    void Renderer::Shutdown()
    {
        m_RenderingAPI = std::shared_ptr<RenderingAPI>();
    }

    void Renderer::BeginFrame()
    {
        m_RenderingAPI->BeginFrame();
    }

    void Renderer::EndFrame()
    {
        m_RenderingAPI->EndFrame();
    }

    void Renderer::DrawPyramid(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawSphere(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawCube(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawCircle(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawLine(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawTriangle(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawQuad(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawTexture(const std::string texture, const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawMesh(const Mesh mesh, const std::string texture, const Material material, const glm::mat4 transform)
    {
    }
}