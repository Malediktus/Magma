#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Renderer/VertexBuffer.h>
#include <Magma/Renderer/IndexBuffer.h>

namespace Magma
{
    class RenderingAPI
    {
    public:
        virtual ~RenderingAPI() = default;

        virtual void Clear(const glm::vec4 &color) const = 0;
        virtual void DrawIndexed(const VertexBuffer *vertexBuffer, const IndexBuffer *indexBuffer, const bool wireframes) const = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window);
}
