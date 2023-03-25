#include <Magma/pch.h>
#include <Magma/Core/Application.h>
#include <Magma/Core/Logger.h>
#include <Magma/Core/Input.h>
#include <Magma/Renderer/Renderer.h>

RenderingAPIType currentRenderingAPI = RenderingAPIType::OpenGL;

namespace Magma
{
    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},

        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},

        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}}};

    const std::vector<uint32_t> indices = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };

    Mesh mesh;
    Material material;
    glm::mat4 transform{1.0f};

    void Application::Run()
    {
        mesh.Vertices = vertices;
        mesh.Indicies = indices;
        material.Color = {0.3f, 0.3f, 0.3f, 1.0f};

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
            Renderer::DrawMesh(mesh, material, transform);
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
