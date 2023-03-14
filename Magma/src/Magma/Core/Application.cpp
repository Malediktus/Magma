#include <Magma/pch.h>
#include <Magma/Core/Application.h>

namespace Magma
{
	void Application::Run()
	{
		OnInit();
		while (mRunning);
		OnShutdown();
	}
}