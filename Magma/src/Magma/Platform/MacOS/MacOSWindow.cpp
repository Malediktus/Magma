#include <Magma/pch.h>

#ifdef MG_PLATFORM_APPLE

#include <Magma/Event/Event.h>
#include <Magma/Core/Window.h>
#include <Magma/Core/Application.h>

#ifdef MG_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

namespace Magma
{
    class MacWindow : public Window
    {
    public:
        MacWindow(const char *title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
            : m_Title(title), m_Width(width), m_Height(height)
        {
            glfwInit();

            if (currentRenderingAPI == RenderingAPIType::OpenGL)
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr);
            if (currentRenderingAPI == RenderingAPIType::OpenGL)
                glfwMakeContextCurrent(m_Window);

            glfwSetKeyCallback(m_Window, KeyCallback);
            glfwSetMouseButtonCallback(m_Window, ButtonCallback);
            glfwSetCursorPosCallback(m_Window, MotionCallback);
            glfwSetFramebufferSizeCallback(m_Window, ResizeCallback);
            glfwSetWindowCloseCallback(m_Window, CloseCallback);
            glfwSetScrollCallback(m_Window, ScrollCallback);
        }

        ~MacWindow()
        {
            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }

        const int &GetWidth() override
        {
            glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
            return m_Width;
        }

        const int &GetHeight() override
        {
            glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
            return m_Height;
        }

        const std::string &GetTitle() const override
        {
            return m_Title;
        }

        void *GetWindowEventHandle() const override
        {
            return m_Window;
        }

        void Update() override
        {
            glfwPollEvents();
        }

        void Draw() override
        {
            glfwSwapBuffers(m_Window);
        }

    protected:
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            // TODO: Translate keycodes. Its ok for now because my keycodes match the ones from glfw
            if (action == GLFW_PRESS)
            {
                KeyPressEvent event((KeyCode &)key);
                EventDispatcher::Post(event);
                return;
            }
            else if (action == GLFW_REPEAT)
            {
                KeyRepeatEvent event((KeyCode &)key);
                EventDispatcher::Post(event);
                return;
            }
            KeyReleaseEvent event((KeyCode &)key);
            EventDispatcher::Post(event);
        }

        static void ButtonCallback(GLFWwindow *window, int button, int action, int mods)
        {
            // TODO: Translate keycodes. Its ok for now because my keycodes match the ones from glfw
            if (action == GLFW_PRESS)
            {
                MousePressEvent event((KeyCode &)button);
                EventDispatcher::Post(event);
                return;
            }
            MouseReleaseEvent event((KeyCode &)button);
            EventDispatcher::Post(event);
        }

        static void MotionCallback(GLFWwindow *window, double xpos, double ypos)
        {
            MouseMoveEvent event(xpos, ypos);
            EventDispatcher::Post(event);
        }

        static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
        {
            MouseScrollEvent event(yoffset);
            EventDispatcher::Post(event);
        }

        static void ResizeCallback(GLFWwindow *window, int width, int height)
        {
            WindowResizeEvent event(width, height);
            EventDispatcher::Post(event);
        }

        static void CloseCallback(GLFWwindow *window)
        {
            WindowCloseEvent event;
            EventDispatcher::Post(event);
        }

        int m_Width;
        int m_Height;
        std::string m_Title;
        GLFWwindow *m_Window;
    };

    std::shared_ptr<Window> WindowCreate(const char *title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<Window>(new MacWindow(title, x, y, width, height));
    }
}

#endif
