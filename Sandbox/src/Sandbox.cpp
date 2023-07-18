#include <CyEngine.h>

#include "CyEngine/Objects/CameraObject.h"
#include "CyEngine/Objects/CubeObject.h"

using namespace Cy;

class Sandbox : public Application
{
public:
	virtual void OnStart() override;
	virtual void OnRunBegin() override;

private:
	CameraObject* m_Camera;
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
	m_Camera = scene->CreateSceneObject<CameraObject>(Vector3(0,0,2), Quat::Identity);
	m_Camera->InitPerspectiveCamera({ 45.0f, 1280, 720, 0.1f, 150.0f });
	scene->CreateSceneObject<CubeObject>(Vector3::Zero, Quat::Identity);
}

void Sandbox::OnRunBegin()
{
	Application::OnRunBegin();

	CY_LOG("Testing rotation on tick ");
	m_Camera->GetTransform().RotateAround(Vector3::Zero, 0.1f, Vector3::Up);
}
