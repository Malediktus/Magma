#include <Magma/pch.h>
#include <Magma/Renderer/VertexBuffer.h>

#include <glad/glad.h>

namespace Magma {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const std::vector<RawVertex>& vertices)
        {
            glGenVertexArrays(1, &m_ArrayId);
            glBindVertexArray(m_ArrayId);
            glGenBuffers(1, &m_BufferId);
            glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)offsetof(RawVertex, Position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)offsetof(RawVertex, Color));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)offsetof(RawVertex, TexCoords));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)offsetof(RawVertex, TextureId));
            glEnableVertexAttribArray(3);
        }

        ~OpenGLVertexBuffer() 
        {
            glDeleteBuffers(1, &m_BufferId);
            glDeleteVertexArrays(1, &m_ArrayId);
        }

        void Bind() const override
        {
            glBindVertexArray(m_ArrayId);
        }

        void Unbind() const override
        {
            glBindVertexArray(0);
        }

    private:
        unsigned int m_BufferId;
        unsigned int m_ArrayId;
    };

    std::shared_ptr<VertexBuffer> VertexBufferCreate(const std::vector<RawVertex>& vertices)
    {
        return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices));
    }
}
