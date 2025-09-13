#pragma once

#ifdef JADI_PLATFORM_WINDOWS

extern JADI::Application* JADI::CreateApplication();

int main(int argc, char** argv)
{
	auto app = JADI::CreateApplication();
	app->Run();
	delete app;
}
#endif