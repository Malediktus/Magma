#include <Magma/pch.h>
#include <Magma/Platform/OpenGL/OpenGLRenderingAPI.h>

namespace Magma
{
    OpenGLRenderingAPI::OpenGLRenderingAPI(Window *window)
        : m_Window(window)
    {
        MG_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");
        glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // ImGui
        // ImGui::CreateContext();
        // ImGui::StyleColorsDark();
        // ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_Window->GetWindowEventHandle(), true);
        // ImGui_ImplOpenGL3_Init("#version 120");
    }

    OpenGLRenderingAPI::~OpenGLRenderingAPI()
    {
        // ImGui
        // ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        // ImGui::DestroyContext();
    }

    void OpenGLRenderingAPI::Clear(const glm::vec4 &color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderingAPI::DrawIndexed(const size_t numIndices, const bool wireframes) const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (wireframes)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderingAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const
    {
        glViewport(x, y, width, height);
    }
}
