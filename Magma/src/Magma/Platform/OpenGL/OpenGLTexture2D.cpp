#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLTexture2D.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Magma
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string &filename)
    {
        int w, h, bits;

        stbi_set_flip_vertically_on_load(1);
        auto *pixels = stbi_load(filename.c_str(), &w, &h, &bits, STBI_rgb_alpha);
        glGenTextures(1, &m_TextureId);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        stbi_image_free(pixels);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureId);
    }

    void OpenGLTexture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
    }
}
