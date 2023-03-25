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
    
    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("ImGui Test Window");
        ImGui::End();
    }
};

Magma::Application* Magma::CreateApplication()
{
	return new SandboxApp;
}
