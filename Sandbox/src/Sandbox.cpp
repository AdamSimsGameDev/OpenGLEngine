#include <CyEngine.h>

class Sandbox : public Cy::Application
{
public:
	Sandbox()
	{
		PushLayer(new Cy::ImGuiLayer());
	}

	~Sandbox()
	{

	}


};

Cy::Application* Cy::CreateApplication()
{
	return new Sandbox();
}