#include <Magma/pch.h>
#include <Magma/Core/Platform.h>
#include <Magma/Renderer/Shader.h>
#include <Magma/Platform/OpenGL/OpenGLShader.h>

namespace Magma
{
    std::shared_ptr<Shader> ShaderCreate(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
    {
        switch (currentRenderingAPI)
        {
        case RenderingAPIType::OpenGL:
            return std::shared_ptr<Shader>(new OpenGLShader(vertexShaderFilename, fragmentShaderFilename));
        }
    }
}