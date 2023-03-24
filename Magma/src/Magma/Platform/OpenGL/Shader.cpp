#pragma once

#ifdef MG_OPENGL

#include <Magma/pch.h>

#include <glad/glad.h>
#include <Magma/Renderer/Shader.h>

namespace Magma {
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
        {
            m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            auto vertexShaderSource = ReadFile(vertexShaderFilename);
            const char* vertexShaderCSource = vertexShaderSource.c_str(); // TODO: Maybe unsafe to do, dont know
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
            const char* fragmentShaderCSource = fragmentShaderSource.c_str(); // TODO: Maybe unsafe to do, dont know
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

        ~OpenGLShader()
        {
            glDeleteProgram(m_ProgramId);
        }

        void Bind() const override
        {
            glUseProgram(m_ProgramId);
        }

        void Unbind() const override
        {
            glUseProgram(0);
        }

        const unsigned int& GetId() { return m_ProgramId; }

    private:
        static const std::string ReadFile(const std::string &filename)
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
    };

    std::shared_ptr<Shader> ShaderCreate(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
    {
        return std::shared_ptr<Shader>(new OpenGLShader(vertexShaderFilename, fragmentShaderFilename));
    }
}

#endif
