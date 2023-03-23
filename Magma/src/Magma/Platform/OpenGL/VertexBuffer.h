#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Magma/Platform/OpenGL/Vertex.h>

namespace Magma {
    class OpenGLVertexBuffer {
    public:
        OpenGLVertexBuffer(const std::vector<OpenGLVertex> vertices)
        {
            glGenVertexArrays(1, &m_ArrayId);
            glBindVertexArray(m_ArrayId);
            glGenBuffers(1, &m_BufferId);
            glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        }

        void Bind()
        {
            glBindVertexArray(m_ArrayId);
        }

    private:
        unsigned int m_BufferId;
        unsigned int m_ArrayId;
    };
}

#endif
