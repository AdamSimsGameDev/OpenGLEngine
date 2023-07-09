#include <CyEngine.h>

class Sandbox : public Cy::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}


};

Cy::Application* Cy::CreateApplication()
{
	return new Sandbox();
}