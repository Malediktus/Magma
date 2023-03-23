#pragma once

#include <Magma/pch.h>

namespace Magma
{
    struct RawVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoords;
        int TextureId;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Append(std::vector<RawVertex> data) = 0;
        virtual void Reset() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void *GetNative() const = 0;
    };

    std::shared_ptr<VertexBuffer> VertexBufferCreate();
}
