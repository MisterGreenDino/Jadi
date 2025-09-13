#pragma once

#ifdef JADI_PLATFORM_WINDOWS

extern JADI::Application* JADI::CreateApplication();

int main(int argc, char** argv)
{
	JADI::Log::Init();
	JADI_CORE_INFO("JADI Log Not initialized");
	JADI_WARN("Client log Initialized");

	auto app = JADI::CreateApplication();
	app->Run();
	delete app;
}
#endif