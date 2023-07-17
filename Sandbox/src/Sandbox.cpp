#include <CyEngine.h>

#include "CyEngine/Objects/CubeObject.h"

using namespace Cy;

class Sandbox : public Application
{
public:
	virtual void OnStart() override;
};

Cy::Application* Cy::CreateApplication()
{
	return new Sandbox();
}

void Sandbox::OnStart()
{
	// Create the scene
	Scene* scene = new Scene();
	AddScene(scene);
	scene->CreateSceneObject<CubeObject>(Vector3::Zero, Quat::Identity);
}
