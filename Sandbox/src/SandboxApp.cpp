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

	void Render() override
	{
		
	}

	void Update() override
	{
		
	}
};

JADI::Application* JADI::CreateApplication()
{
	return new Sandbox();
}