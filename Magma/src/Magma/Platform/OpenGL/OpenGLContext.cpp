#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLContext.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Magma;

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
: m_WindowHandle(windowHandle)
{
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    MG_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
