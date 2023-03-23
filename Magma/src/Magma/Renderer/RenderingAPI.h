#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>

namespace Magma
{
    class RenderingAPI
    {
    public:
        virtual ~RenderingAPI() = default;

        virtual void Clear(glm::vec4 color) = 0;
        virtual void DrawIndexed(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer, bool wireframes) = 0;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window);
}
