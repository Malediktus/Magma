#include <Magma/pch.h>
#include <Magma/Platform/Vulkan/VulkanShader.h>

namespace Magma
{
    VulkanShader::VulkanShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
    {
    }

    VulkanShader::~VulkanShader()
    {
    }

    void VulkanShader::Bind() const
    {
    }

    void VulkanShader::Unbind() const
    {
    }

    void VulkanShader::UploadInt(const std::string &name, const unsigned int value) const
    {
    }

    void VulkanShader::UploadMat4(const std::string &name, const glm::mat4 &value) const
    {
    }
}
