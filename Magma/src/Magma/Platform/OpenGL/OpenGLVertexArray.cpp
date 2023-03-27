#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLVertexArray.h>

#include <glad/glad.h>

using namespace Magma;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case Magma::ShaderDataType::Float:    return GL_FLOAT;
        case Magma::ShaderDataType::Float2:   return GL_FLOAT;
        case Magma::ShaderDataType::Float3:   return GL_FLOAT;
        case Magma::ShaderDataType::Float4:   return GL_FLOAT;
        case Magma::ShaderDataType::Mat3:     return GL_FLOAT;
        case Magma::ShaderDataType::Mat4:     return GL_FLOAT;
        case Magma::ShaderDataType::Int:      return GL_INT;
        case Magma::ShaderDataType::Int2:     return GL_INT;
        case Magma::ShaderDataType::Int3:     return GL_INT;
        case Magma::ShaderDataType::Int4:     return GL_INT;
        case Magma::ShaderDataType::Bool:     return GL_BOOL;
        default: MG_ASSERT_MSG(false, "Unknown ShaderDataType!");
    }

    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    MG_ASSERT_MSG(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
    
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();
    
    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              (const void*)element.Offset);
        index++;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}
