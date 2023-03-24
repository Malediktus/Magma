#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Renderer/RenderingAPI.h>
#include <Magma/Renderer/RenderCommand.h>

#include <glm/glm.hpp>

namespace Magma
{
    struct Material
    {
        glm::vec4 Color;
    };

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec2 TexCoords;
    };

    struct Mesh
    {
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indicies;
    };

    class Renderer
    {
    public:
        static void Init(Window *window);

        static void BeginFrame();
        static void EndFrame();

        static void DrawTexture(const std::string &texture, const Material &material, const glm::mat4 &transform);
        static void DrawMesh(const Mesh& mesh, const Material& material, const glm::mat4& transform);
        static void DrawMesh(const Mesh &mesh, const std::string &texture, const Material &material, const glm::mat4 &transform);
    };
}
