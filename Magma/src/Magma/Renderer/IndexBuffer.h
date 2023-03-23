#pragma once

#include <Magma/pch.h>

namespace Magma
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Append(std::vector<uint32_t> data) = 0;
        virtual void Reset() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void *GetNative() const = 0;
    };

    std::shared_ptr<IndexBuffer> IndexBufferCreate();
}
