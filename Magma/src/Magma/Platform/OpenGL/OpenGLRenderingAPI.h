#pragma once

#include <Magma/Renderer/RenderingAPI.h>

#include <glad/glad.h>
// TODO: Make window implementation independent
#include <GLFW/glfw3.h>

namespace Magma
{
    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        OpenGLRenderingAPI(Window *window);
        ~OpenGLRenderingAPI();

        void Clear(const glm::vec4 &color) const override;
        void DrawIndexed(const size_t numIndices, const bool wireframes) const override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;

    private:
        Window *m_Window;
    };
}
