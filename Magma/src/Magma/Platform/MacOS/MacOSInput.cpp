#include <Magma/pch.h>

#ifdef MG_PLATFORM_APPLE

#include <Magma/Core/Window.h>
#include <Magma/Core/Input.h>
#include <GLFW/glfw3.h>

using namespace Magma;

std::shared_ptr<Window> Input::m_Window;

void Input::Init(std::shared_ptr<Window> window)
{
    m_Window = window;
}

bool Input::GetKey(KeyCode key)
{
    // TODO: Translate keycode
    return glfwGetKey((GLFWwindow *)m_Window->GetNative(), key) == GLFW_PRESS;
}

int Input::GetMouseX()
{
    double x;
    double y;
    glfwGetCursorPos((GLFWwindow *)m_Window->GetNative(), &x, &y);
    return x;
}

int Input::GetMouseY()
{
    double x;
    double y;
    glfwGetCursorPos((GLFWwindow *)m_Window->GetNative(), &x, &y);
    return y;
}

std::pair<int, int> Input::GetMousePos()
{
    double x;
    double y;
    glfwGetCursorPos((GLFWwindow *)m_Window->GetNative(), &x, &y);
    return std::make_pair(x, y);
}

#endif
