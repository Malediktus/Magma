#include <Magma/Renderer/Renderer.h>

namespace Magma
{
    void Renderer::Init(Window *window)
    {
        RenderCommand::Init(window);
        RenderCommand::SetViewport(0, 0, window->GetWidth(), window->GetHeight());
        
        EventDispatcher::Subscribe<WindowResizeEvent>(OnResize);
    }

    void Renderer::Shutdown()
    {
        RenderCommand::Shutdown();
    }

    void Renderer::BeginFrame()
    {
        RenderCommand::Clear({0.0f, 0.0f, 0.0f, 1.0f});
    }

    void Renderer::EndFrame()
    {
    }

    void Renderer::DrawTexture(const Texture2D &texture, const Material &material, const glm::mat4 &transform)
    {
        const std::vector<Vertex> Vertices = {
            {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}};

        const std::vector<uint32_t> Indicies = {
            0, 1, 3,
            1, 2, 3};

        std::vector<RawVertex> vertices;
        vertices.resize(Vertices.size());
        for (size_t i = 0; i < Vertices.size(); i++)
        {
            vertices[i].Position = Vertices[i].Position;
            vertices[i].TexCoords = Vertices[i].TexCoords;
            vertices[i].Color = material.Color;
        }

        texture.Bind();
        RenderCommand::DrawIndexed(vertices, Indicies, transform, true);
    }

    void Renderer::DrawMesh(const Mesh &mesh, const Texture2D &texture, const Material &material, const glm::mat4 &transform)
    {
        std::vector<RawVertex> vertices;
        vertices.resize(mesh.Vertices.size());
        for (size_t i = 0; i < mesh.Vertices.size(); i++)
        {
            vertices[i].Position = mesh.Vertices[i].Position;
            vertices[i].TexCoords = mesh.Vertices[i].TexCoords;
            vertices[i].Color = material.Color;
        }

        texture.Bind();
        RenderCommand::DrawIndexed(vertices, mesh.Indicies, transform, true);
    }

    void Renderer::DrawMesh(const Mesh &mesh, const Material &material, const glm::mat4 &transform)
    {
        std::vector<RawVertex> vertices;
        vertices.resize(mesh.Vertices.size());
        for (size_t i = 0; i < mesh.Vertices.size(); i++)
        {
            vertices[i].Position = mesh.Vertices[i].Position;
            vertices[i].TexCoords = mesh.Vertices[i].TexCoords;
            vertices[i].Color = material.Color;
        }

        RenderCommand::DrawIndexed(vertices, mesh.Indicies, transform, false);
    }

    void Renderer::OnResize(const Event &e)
    {
        const WindowResizeEvent &resizeEvent = static_cast<const WindowResizeEvent&>(e);
        RenderCommand::SetViewport(0, 0, resizeEvent.GetWidth(), resizeEvent.GetHeight());
    }
}
