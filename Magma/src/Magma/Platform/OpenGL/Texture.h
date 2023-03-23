#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>

namespace Magma {
    class OpenGLTexture {
    public:
        OpenGLTexture(const std::string filename)
        {
            int w, h, bits;

            stbi_set_flip_vertically_on_load(1);
            auto* pixels = stbi_load(filename.c_str(), &w, &h, &bits, STBI_rgb);
            glGenTextures(1, &m_TextureId);
            glBindTexture(GL_TEXTURE_2D, m_TextureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            stbi_image_free(pixels);
        }

        ~OpenGLTexture()
        {
            glDeleteTextures(1, &m_TextureId);
        }

        void Bind()
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_TextureId);
        }

    private:
        unsigned int m_TextureId;
    };
}

#endif
