#include <Magma/pch.h>

#ifdef MG_PLATFORM_WINDOWS

#include <Magma/Core/Input.h>
#include <GLFW/glfw3.h>

namespace Magma
{
    void* Input::mWindowEventHandle = nullptr;

    void Input::Init(void* WindowEventHandle)
    {
        mWindowEventHandle = WindowEventHandle;
    }

    bool Input::GetKey(KeyCode key)
    {
        // TODO: Translate keycode
        return glfwGetKey((GLFWwindow*)mWindowEventHandle, key) == GLFW_PRESS;
    }

    int Input::GetMouseX()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow*)mWindowEventHandle, &x, &y);
        return x;
    }

    int Input::GetMouseY()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow*)mWindowEventHandle, &x, &y);
        return y;
    }

    std::pair<int, int> Input::GetMousePos()
    {
        double x;
        double y;
        glfwGetCursorPos((GLFWwindow*)mWindowEventHandle, &x, &y);
        return std::make_pair(x, y);
    }
}

#endif