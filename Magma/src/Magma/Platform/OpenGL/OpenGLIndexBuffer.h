#pragma once

#include <Magma/Renderer/IndexBuffer.h>

#include <glad/glad.h>

namespace Magma
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const std::vector<uint32_t> &indices);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
        size_t Size() const override;

    private:
        size_t m_Size;
        unsigned int m_BufferId;
    };
}
