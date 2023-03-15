#pragma once

#include <gc_cpp.h>

namespace Magma
{
	class Application : public gc
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();

		virtual void OnInit() = 0;
		virtual void OnShutdown() = 0;
		virtual void OnUpdate() = 0;

	private:
		bool mRunning;
	};

	Application* CreateApplication();
}