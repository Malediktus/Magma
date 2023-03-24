#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLVertexBuffer.h>

#include <glad/glad.h>

namespace Magma
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<RawVertex> &vertices)
    {
        glGenVertexArrays(1, &m_ArrayId);
        glBindVertexArray(m_ArrayId);
        glGenBuffers(1, &m_BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)offsetof(RawVertex, Position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)offsetof(RawVertex, Color));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)offsetof(RawVertex, TexCoords));
        glEnableVertexAttribArray(2);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
        glDeleteVertexArrays(1, &m_ArrayId);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindVertexArray(m_ArrayId);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindVertexArray(0);
    }
}
