#include <Magma/pch.h>
#include <Magma/Core/Application.h>

namespace Magma
{
	void Application::Run()
	{
		EASY_FUNCTION(profiler::colors::Red);

		OnInit();
		while (mRunning);
		OnShutdown();
	}
}