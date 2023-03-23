#include <Magma/pch.h>
#ifdef MG_OPENGL

#include <glad/glad.h>
// TODO: Make window implementation independent
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Magma/Event/Event.h>
#include <Magma/Renderer/RenderingAPI.h>

#include <Magma/Platform/OpenGL/Vertex.h>
#include <Magma/Platform/OpenGL/VertexBuffer.h>
#include <Magma/Platform/OpenGL/IndexBuffer.h>
#include <Magma/Platform/OpenGL/Shader.h>
#include <Magma/Platform/OpenGL/Texture.h>

namespace Magma
{
    const std::vector<OpenGLVertex> vertices = {
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        OpenGLRenderingAPI(Window *window)
            : m_Window(window)
        {
            MG_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");
            glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
            EventDispatcher::Subscribe<WindowResizeEvent>(std::bind(&OpenGLRenderingAPI::OnResize, this, std::placeholders::_1));

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            m_Shader = std::unique_ptr<OpenGLShader>(new OpenGLShader("assets/Base.vert", "assets/Base.frag"));
            m_VertexBuffer = std::unique_ptr<OpenGLVertexBuffer>(new OpenGLVertexBuffer(vertices));
            m_IndexBuffer = std::unique_ptr<OpenGLIndexBuffer>(new OpenGLIndexBuffer(indices));
            m_Texture = std::unique_ptr<OpenGLTexture>(new OpenGLTexture("assets/MagmaIcon.png"));

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)offsetof(OpenGLVertex, Position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)offsetof(OpenGLVertex, Color));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)offsetof(OpenGLVertex, TexCoord));
            glEnableVertexAttribArray(2);

            // ImGui
            ImGui::CreateContext();
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_Window->GetWindowEventHandle(), true);
            ImGui_ImplOpenGL3_Init("#version 120");
        }

        ~OpenGLRenderingAPI()
        {
            // ImGui
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void BeginFrame() override
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void EndFrame() override
        {
            m_VertexBuffer->Bind();
            m_IndexBuffer->Bind();
            m_Texture->Bind();
            m_Shader->Bind();
            glUniform1i(glGetUniformLocation(m_Shader->GetId(), "TextureId"), 0);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }
        
        void BeginGui() override
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
        
        void EndGui() override
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

    private:
        void OnResize(const Event &e)
        {
            glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
        }

        Window *m_Window;

        std::unique_ptr<OpenGLVertexBuffer> m_VertexBuffer;
        std::unique_ptr<OpenGLIndexBuffer> m_IndexBuffer;
        std::unique_ptr<OpenGLShader> m_Shader;
        std::unique_ptr<OpenGLTexture> m_Texture;
    };

    std::shared_ptr<RenderingAPI> RenderingAPICreate(Window *window)
    {
        return std::shared_ptr<RenderingAPI>(new OpenGLRenderingAPI(window));
    }
}

#endif
