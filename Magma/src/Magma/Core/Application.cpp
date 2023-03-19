#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>
#include <Magma/Core/Input.h>
#include <Magma/Renderer/Renderer.h>

namespace Magma
{
    void Application::Run()
    {
        EASY_FUNCTION(profiler::colors::Red);
        m_Running = true;
        Logger::Init();
        EventDispatcher::Subscribe<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        m_Window = WindowCreate("Magma Engine", 0, 0, 1080, 720);
        Input::Init(m_Window->GetWindowEventHandle());
        Renderer::Init(m_Window.get());
        OnInit();

        while (m_Running)
        {
            m_Window->Update();
            Renderer::BeginFrame();
            Renderer::EndFrame();
            m_Window->Draw();
        }

        OnShutdown();
        Renderer::Shutdown();
    }

    void Application::OnWindowClose(const Event &)
    {
        m_Running = false;
    }
}