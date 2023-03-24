#include <Magma/pch.h>
#include <Magma/Renderer/IndexBuffer.h>

#include <glad/glad.h>

namespace Magma {
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const std::vector<uint32_t> &indices)
            : m_Size(indices.size())
        {
            glGenBuffers(1, &m_BufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
        }

        ~OpenGLIndexBuffer()
        {
            glDeleteBuffers(1, &m_BufferId);
        }

        void Bind() const override
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        }

        void Unbind() const override
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        size_t Size() const override
        {
            return m_Size;
        }

    private:
        size_t m_Size;
        unsigned int m_BufferId;
    };

    std::shared_ptr<IndexBuffer> IndexBufferCreate(const std::vector<uint32_t>& indices)
    {
        return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices));
    }
}
