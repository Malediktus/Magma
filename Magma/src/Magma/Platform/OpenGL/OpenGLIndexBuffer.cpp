#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLIndexBuffer.h>

namespace Magma
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t> &indices)
        : m_Size(indices.size())
    {
        glGenBuffers(1, &m_BufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t OpenGLIndexBuffer::Size() const
    {
        return m_Size;
    }
}
