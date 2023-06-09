#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Scene/Camera.h>
#include <Magma/Renderer/Renderer.h>
#include <Magma/Renderer/RenderingAPI.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Renderer/IndexBuffer.h>
#include <Magma/Renderer/Shader.h>

namespace Magma
{
    class RenderCommand
    {
    public:
        static void Init(Window *window);
        static void Shutdown();
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void Clear(const glm::vec4 &color);
        static void DrawIndexed(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform, const bool useTexture);
        static void DrawIndexedWireframe(const std::vector<RawVertex> &vertices, const std::vector<uint32_t> &indices, const glm::mat4 &transform, const bool useTexture);
        static std::shared_ptr<RenderingAPI> GetRenderingAPI() { return m_RenderingAPI; }

    private:
        static void OnReisze(const Event &e);
        
        static std::shared_ptr<RenderingAPI> m_RenderingAPI;
        static std::shared_ptr<Shader> m_BaseShader;
        static std::shared_ptr<Shader> m_TextureShader;
        static std::unique_ptr<Camera> m_Camera;
    };
}
