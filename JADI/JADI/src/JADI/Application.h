#pragma once

#include "Core.h"

namespace JADI {
	class JADI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in a client
	Application* CreateApplication();
}
