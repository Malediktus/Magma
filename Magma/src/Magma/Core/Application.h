#pragma once

#include <Magma/pch.h>
#include <Magma/Core/Window.h>
#include <Magma/Event/Event.h>

namespace Magma
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
		void OnWindowClose(const Event &);

		virtual void OnInit() = 0;
		virtual void OnShutdown() = 0;
		virtual void OnUpdate() = 0;

	private:
		std::shared_ptr<Window> m_Window;
		bool m_Running;
	};

	Application *CreateApplication();
}