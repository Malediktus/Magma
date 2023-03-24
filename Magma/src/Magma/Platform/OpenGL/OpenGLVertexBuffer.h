#pragma once
#include <Magma/Renderer/VertexBuffer.h>

namespace Magma
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const std::vector<RawVertex> &vertices);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

    private:
        unsigned int m_BufferId;
        unsigned int m_ArrayId;
    };
}
