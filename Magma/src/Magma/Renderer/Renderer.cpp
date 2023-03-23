#include <Magma/Renderer/Renderer.h>

namespace Magma
{
    void Renderer::Init(Window *window)
    {
        RenderCommand::Init(window);
    }

    void Renderer::BeginFrame()
    {
        RenderCommand::Clear({0.0f, 0.0f, 0.0f, 1.0f});
        RenderCommand::NewFrame();
    }

    void Renderer::EndFrame()
    {
        RenderCommand::DrawIndexed();
    }

    void Renderer::DrawCircle(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawLine(const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawTexture(const std::string texture, const Material material, const glm::mat4 transform)
    {
    }

    void Renderer::DrawMesh(const Mesh mesh, const std::string texture, const Material material, const glm::mat4 transform)
    {
    }
}
