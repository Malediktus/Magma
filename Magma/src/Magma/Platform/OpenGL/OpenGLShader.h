#pragma once

#include <Magma/Renderer/Shader.h>

namespace Magma
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;

        void UploadInt(const std::string &name, const unsigned int value) const override;
        void UploadMat4(const std::string &name, const glm::mat4 &value) const override;

        const unsigned int &GetId();

    private:
        static const std::string ReadFile(const std::string &filename);

        unsigned int m_VertexShaderId;
        unsigned int m_FragmentShaderId;
        unsigned int m_ProgramId;
    };
}
