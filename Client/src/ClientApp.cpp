#include <Magma/Magma.h>

class SandboxApp : public Magma::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
    
    void OnInit() override
    {
        m_ShowDemoWindow = true;
    }
    
    void OnShutdown() override
    {
    }
    
    void OnUpdate() override
    {
    }
    
    void OnDebugUIRender() override
    {
        if (m_ShowDemoWindow)
            ImGui::ShowDemoWindow(&m_ShowDemoWindow);
        ImGui::Begin("Test");
        ImGui::Text("ImGui Test Window");
        ImGui::End();
    }
    
private:
    bool m_ShowDemoWindow;
};

std::shared_ptr<Magma::Application> Magma::CreateApplication()
{
    return std::make_shared<SandboxApp>();
}
