#pragma once

#include <Magma/pch.h>

namespace Magma
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual size_t Size() const = 0;
    };

    std::shared_ptr<IndexBuffer> IndexBufferCreate(const std::vector<uint32_t> &indices);
}
