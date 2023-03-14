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
};

Magma::Application* Magma::CreateApplication()
{
	return new SandboxApp;
}