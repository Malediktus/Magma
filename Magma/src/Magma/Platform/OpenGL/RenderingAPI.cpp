#include <Magma/pch.h>
#ifdef MG_OPENGL

#include <glad/glad.h>
// TODO: Make window implementation independent
#include <GLFW/glfw3.h>

#include <Magma/Renderer/RenderingAPI.h>

void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

namespace Magma
{
    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        OpenGLRenderingAPI(Window *window)
            : m_Window(window)
        {
            MG_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");
            glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

            // ImGui
            // ImGui::CreateContext();
            // ImGui::StyleColorsDark();
            // ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_Window->GetWindowEventHandle(), true);
            // ImGui_ImplOpenGL3_Init("#version 120");
        }

        ~OpenGLRenderingAPI()
        {
            // ImGui
            // ImGui_ImplOpenGL3_Shutdown();
            // ImGui_ImplGlfw_Shutdown();
            // ImGui::DestroyContext();
        }

        void Clear(const glm::vec4& color) const override
        {
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void DrawIndexed(const size_t numIndices, const bool wireframes) const override
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            if (wireframes)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
        }

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override
        {
            glViewport(x, y, width, height);
        }

    private:
        Window *m_Window;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        return std::shared_ptr<RenderingAPI>(new OpenGLRenderingAPI(window));
    }
}

#endif
