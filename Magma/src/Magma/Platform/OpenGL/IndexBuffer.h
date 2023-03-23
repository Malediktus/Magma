#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Magma {
    class OpenGLIndexBuffer {
    public:
        OpenGLIndexBuffer(const std::vector<uint32_t> indices)
        {
            glGenBuffers(1, &m_BufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
        }

        void Bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
        }

    private:
        unsigned int m_BufferId;
    };
}

#endif
