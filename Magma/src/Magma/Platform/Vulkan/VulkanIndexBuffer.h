#pragma once

#include <Magma/Renderer/IndexBuffer.h>

namespace Magma
{
    class VulkanIndexBuffer : public IndexBuffer
    {
    public:
        VulkanIndexBuffer(const std::vector<uint32_t> &indices);
        ~VulkanIndexBuffer();
        void Bind() const override;
        void Unbind() const override;
        size_t Size() const override;
    };
}
