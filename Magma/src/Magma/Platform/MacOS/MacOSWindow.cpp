#include <Magma/pch.h>

#ifdef MG_PLATFORM_APPLE

#include <Magma/Event/Event.h>
#include <Magma/Core/Window.h>
#include <Magma/Core/Application.h>
#include <Magma/Renderer/GraphicsContext.h>

#include <GLFW/glfw3.h>

namespace Magma
{
class MacWindow : public Window
{
public:
    MacWindow(const std::string& title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    : m_Title(title)
    {
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        m_Window = glfwCreateWindow(width, height, m_Title.c_str(), nullptr, nullptr);
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
    
    const int& GetWidth() override
    {
        glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
        return m_Width;
    }
    
    const int& GetHeight() override
    {
        glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
        return m_Height;
    }
    
    const std::string& GetTitle() const override
    {
        return m_Title;
    }
    
    void* GetNative() const override
    {
        return m_Window;
    }
    
    void Update() override
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
    
protected:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        // TODO: Translate keycodes
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
    
    static void ButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            MousePressEvent event((KeyCode &)button);
            EventDispatcher::Post(event);
            return;
        }
        MouseReleaseEvent event((KeyCode &)button);
        EventDispatcher::Post(event);
    }
    
    static void MotionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        MouseMoveEvent event(xpos, ypos);
        EventDispatcher::Post(event);
    }
    
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        MouseScrollEvent event(yoffset);
        EventDispatcher::Post(event);
    }
    
    static void ResizeCallback(GLFWwindow* window, int width, int height)
    {
        WindowResizeEvent event(width, height);
        EventDispatcher::Post(event);
    }
    
    static void CloseCallback(GLFWwindow* window)
    {
        WindowCloseEvent event;
        EventDispatcher::Post(event);
    }
    
    int m_Width;
    int m_Height;
    const std::string m_Title;
    GLFWwindow *m_Window;
    std::shared_ptr<GraphicsContext> m_Context;
};

std::shared_ptr<Window> WindowCreate(const std::string& title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    return std::make_shared<MacWindow>(title, x, y, width, height);
}
}

#endif
