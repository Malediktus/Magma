#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>
#include <Magma/Core/Input.h>
#include <Magma/UI/DebugUI.h>

RenderingAPIType currentRenderingAPI = RenderingAPIType::OpenGL;

namespace Magma
{
    void Application::Run()
    {
        m_Running = true;
        Logger::Init();
        EventDispatcher::Subscribe<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        m_Window = WindowCreate("Magma Engine", 0, 0, 1080, 720);
        Input::Init(m_Window->GetWindowEventHandle());
        DebugUI::Init(m_Window);
        OnInit();

        while (m_Running)
        {
            m_Window->Update();
            DebugUI::BeginFrame();
            OnImGuiRender();
            DebugUI::EndFrame();
            m_Window->Draw();
        }

        OnShutdown();
        DebugUI::Shutdow();
    }

    void Application::OnWindowClose(const Event &)
    {
        m_Running = false;
    }
}
