#pragma once

#include <Magma/Renderer/Shader.h>

namespace Magma
{
    class VulkanShader : public Shader
    {
    public:
        VulkanShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
        ~VulkanShader();

        void Bind() const override;
        void Unbind() const override;

        void UploadInt(const std::string &name, const unsigned int value) const override;
        void UploadMat4(const std::string &name, const glm::mat4 &value) const override;
    };
}
