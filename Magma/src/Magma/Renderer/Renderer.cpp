#include <Magma/Renderer/Renderer.h>

namespace Magma
{
    void Renderer::Init(Window *window)
    {
        RenderCommand::Init(window);
        RenderCommand::SetViewport(0, 0, window->GetWidth(), window->GetHeight());
    }

    void Renderer::BeginFrame()
    {
        RenderCommand::Clear({1.0f, 0.0f, 0.0f, 1.0f});
    }

    void Renderer::EndFrame()
    {
    }

    void Renderer::DrawTexture(const std::string &texture, const Material &material, const glm::mat4 &transform)
    {
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
            vertices[i].TextureId = 0;
        }

        RenderCommand::DrawIndexed(vertices, mesh.Indicies, transform);
    }

    void Renderer::DrawMesh(const Mesh& mesh, const std::string& texture, const Material& material, const glm::mat4& transform)
    {
        std::vector<RawVertex> vertices;
        vertices.resize(mesh.Vertices.size());
        for (size_t i = 0; i < mesh.Vertices.size(); i++)
        {
            vertices[i].Position = mesh.Vertices[i].Position;
            vertices[i].TexCoords = mesh.Vertices[i].TexCoords;
            vertices[i].Color = material.Color;
            vertices[i].TextureId = 0;
        }

        RenderCommand::DrawIndexed(vertices, mesh.Indicies, transform);
    }
}
