#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLShader.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Magma
{
    OpenGLShader::OpenGLShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
    {
        m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        auto vertexShaderSource = ReadFile(vertexShaderFilename);
        const char *vertexShaderCSource = vertexShaderSource.c_str(); // TODO: Maybe unsafe to do, dont know
        glShaderSource(m_VertexShaderId, 1, &vertexShaderCSource, NULL);
        glCompileShader(m_VertexShaderId);

        int success;
        glGetShaderiv(m_VertexShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(m_VertexShaderId, 512, NULL, infoLog);
            LOG_FATAL("Failed to Compile Vertex Shader:\n{}", infoLog);
        }

        m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        auto fragmentShaderSource = ReadFile(fragmentShaderFilename);
        const char *fragmentShaderCSource = fragmentShaderSource.c_str(); // TODO: Maybe unsafe to do, dont know
        glShaderSource(m_FragmentShaderId, 1, &fragmentShaderCSource, NULL);
        glCompileShader(m_FragmentShaderId);

        glGetShaderiv(m_FragmentShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(m_FragmentShaderId, 512, NULL, infoLog);
            LOG_FATAL("Failed to Compile Fragment Shader:\n{}", infoLog);
        }

        m_ProgramId = glCreateProgram();
        glAttachShader(m_ProgramId, m_VertexShaderId);
        glAttachShader(m_ProgramId, m_FragmentShaderId);
        glLinkProgram(m_ProgramId);

        glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_ProgramId, 512, NULL, infoLog);
            LOG_FATAL("Failed to Link Shader Program:\n{}", infoLog);
        }

        glDeleteShader(m_VertexShaderId);
        glDeleteShader(m_FragmentShaderId);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ProgramId);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ProgramId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadInt(const std::string &name, const unsigned int value) const
    {
        glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value);
    }

    void OpenGLShader::UploadMat4(const std::string &name, const glm::mat4 &value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    const unsigned int &OpenGLShader::GetId() { return m_ProgramId; }

    const std::string OpenGLShader::ReadFile(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        MG_ASSERT_MSG(file.is_open(), "Failed to open file!");
        file.seekg(0);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    unsigned int m_VertexShaderId;
    unsigned int m_FragmentShaderId;
    unsigned int m_ProgramId;
}
