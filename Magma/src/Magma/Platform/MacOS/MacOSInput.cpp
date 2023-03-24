#include <Magma/pch.h>

#ifdef MG_PLATFORM_APPLE

#include <Magma/Core/Input.h>
#include <GLFW/glfw3.h>

namespace Magma
{
    void *Input::m_WindowEventHandle = nullptr;

    void Input::Init(void *WindowEventHandle)
    {
        m_WindowEventHandle = WindowEventHandle;
    }

    bool Input::GetKey(KeyCode key)
    {
        // TODO: Translate keycode
        return glfwGetKey((GLFWwindow *)m_WindowEventHandle, key) == GLFW_PRESS;
    }

    int Input::GetMouseX()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow *)m_WindowEventHandle, &x, &y);
        return x;
    }

    int Input::GetMouseY()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow *)m_WindowEventHandle, &x, &y);
        return y;
    }

    std::pair<int, int> Input::GetMousePos()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow *)m_WindowEventHandle, &x, &y);
        return std::make_pair(x, y);
    }
}

#endif