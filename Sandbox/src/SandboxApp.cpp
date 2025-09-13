#include <Jadi.h>

class Sandbox : public JADI::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

JADI::Application* JADI::CreateApplication()
{
	return new Sandbox();
}