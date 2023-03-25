#pragma once

#include <Magma/Renderer/VertexBuffer.h>

namespace Magma
{
    class VulkanVertexBuffer : public VertexBuffer
    {
    public:
        VulkanVertexBuffer(const std::vector<RawVertex> &vertices);
        ~VulkanVertexBuffer();
        void Bind() const override;
        void Unbind() const override;
    };
}
