#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/Shader.h>
#include <Magma/Platform/OpenGL/OpenGLShader.h>
#include <Magma/Platform/Vulkan/VulkanShader.h>

namespace Magma
{
    std::shared_ptr<Shader> ShaderCreate(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<Shader>(new OpenGLShader(vertexShaderFilename, fragmentShaderFilename));
        case RenderingAPIType::Vulkan:
            return std::shared_ptr<Shader>(new VulkanShader(vertexShaderFilename, fragmentShaderFilename));
        default:
            MG_ASSERT_NO_MSG(false);
            return std::shared_ptr<Shader>();
        }
    }
}