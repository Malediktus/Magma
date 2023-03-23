#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Magma {
    struct OpenGLVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        
        static void SetVertexFormat()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) offsetof(OpenGLVertex, Position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) offsetof(OpenGLVertex, Color));
            glEnableVertexAttribArray(1);
        }
    };
}

#endif
