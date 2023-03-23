#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Magma {
    struct OpenGLVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        
        static void SetVertexFormat()
        {
        }
    };
}

#endif
