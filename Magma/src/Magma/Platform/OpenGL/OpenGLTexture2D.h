#pragma once

#include <Magma/Renderer/Texture2D.h>

namespace Magma
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string &filename);
        ~OpenGLTexture2D();

        void Bind() const override;

    private:
        unsigned int m_TextureId;
    };
}
