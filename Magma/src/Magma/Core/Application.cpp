#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>
#include <Magma/Core/Input.h>
#include <Magma/UI/DebugUI.h>

#include <Magma/Renderer/Renderer.h>
#include <Magma/Renderer/RenderCommand.h>
#include <Magma/Renderer/Buffer.h>
#include <Magma/Renderer/VertexArray.h>

using namespace Magma;

float vertices[3 * 7] = {
    -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
};

uint32_t indices[3] = { 0, 1, 2 };

void Application::Run()
{
    m_Running = true;
    Logger::Init();
    m_Window = WindowCreate("Magma Engine", 0, 0, 1080, 720);
    Input::Init(m_Window);
    DebugUI::Init(m_Window);
    EventDispatcher::Subscribe<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    RenderCommand::Init();
    RenderCommand::SetClearColor({1.0f, 0.0f, 1.0f, 1.0f});
    OnInit();
    
    std::shared_ptr<VertexArray> vertexArray = VertexArray::Create();
    
    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->SetLayout(layout);
    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    
    while (m_Running)
    {
        RenderCommand::Clear();
        
        DebugUI::BeginFrame();
        OnDebugUIRender();
        DebugUI::EndFrame();
        
        Renderer::BeginScene();
        Renderer::Submit(vertexArray);
        Renderer::EndScene();
        
        m_Window->Update();
    }
    
    OnShutdown();
    DebugUI::Shutdow();
}

void Application::OnWindowClose(const Event&)
{
    m_Running = false;
}
