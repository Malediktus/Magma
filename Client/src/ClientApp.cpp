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
        bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
};

Magma::Application* Magma::CreateApplication()
{
	return new SandboxApp;
}
