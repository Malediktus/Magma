#include <Magma/Magma.h>

class SandboxApp : public Magma::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() = default;
    
    void OnInit() override
    {
    }
    
    void OnShutdown() override
    {
    }
    
    void OnUpdate() override
    {
    }
    
    void OnDebugUIRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("ImGui Test Window");
        ImGui::End();
    }
};

std::shared_ptr<Magma::Application> Magma::CreateApplication()
{
    return std::make_shared<SandboxApp>();
}
