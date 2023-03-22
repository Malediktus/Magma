#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Renderer/RenderingAPI.h>

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
        glm::vec4 Color;
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
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();
        
        static void BeginGui();
        static void EndGui();

        static void DrawPyramid(const Material material, const glm::mat4 transform);
        static void DrawSphere(const Material material, const glm::mat4 transform);
        static void DrawCube(const Material material, const glm::mat4 transform);
        static void DrawCircle(const Material material, const glm::mat4 transform);
        static void DrawLine(const Material material, const glm::mat4 transform);
        static void DrawTriangle(const Material material, const glm::mat4 transform);
        static void DrawQuad(const Material material, const glm::mat4 transform);
        static void DrawTexture(const std::string texture, const Material material, const glm::mat4 transform);
        static void DrawMesh(const Mesh mesh, const std::string texture, const Material material, const glm::mat4 transform);

    private:
        static std::shared_ptr<RenderingAPI> m_RenderingAPI;
    };
}
