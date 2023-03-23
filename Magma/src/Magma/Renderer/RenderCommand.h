#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Renderer/RenderingAPI.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Renderer/IndexBuffer.h>

namespace Magma
{
    class RenderCommand
    {
    public:
        static void Init(const Window *window);
        static void Clear(glm::vec4 color);
        static void Submit(Mesh mesh, glm::mat4 transform);
        static void NewFrame();
        static void DrawIndexed();
        static void DrawIndexedWireframe();

        static RenderingAPI &GetRenderingAPI() const { return m_RenderingAPI; }

    private:
        static std::shared_ptr<RenderingAPI> m_RenderingAPI;
        static std::shared_ptr<VertexBuffer> m_VertexBuffer;
        static std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}