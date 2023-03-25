#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>
#include <Magma/Core/Input.h>
#include <Magma/UI/DebugUI.h>

using namespace Magma;

void Application::Run()
{
    m_Running = true;
    Logger::Init();
    m_Window = WindowCreate("Magma Engine", 0, 0, 1080, 720);
    Input::Init(m_Window);
    DebugUI::Init(m_Window);
    EventDispatcher::Subscribe<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    OnInit();
    
    while (m_Running)
    {
        DebugUI::BeginFrame();
        OnDebugUIRender();
        DebugUI::EndFrame();
        
        m_Window->Update();
    }
    
    OnShutdown();
    DebugUI::Shutdow();
}

void Application::OnWindowClose(const Event&)
{
    m_Running = false;
}
