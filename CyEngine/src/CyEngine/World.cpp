#include "cypch.h"
#include "World.h"
#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Components/MeshComponent.h"
#if CY_EDITOR
#include "Components/EditorCameraComponent.h"
#endif

namespace Cy
{
	World* World::s_Scene = nullptr;

	World::World()
	{
		s_Scene = this;

		ADD_TRACKED_COMPONENT_TYPE(MeshComponent);
		ADD_TRACKED_COMPONENT_TYPE(CameraComponent);
		ADD_TRACKED_COMPONENT_TYPE(LightComponent);
	}

	void World::Tick(float deltaTime)
	{
		for (auto obj : m_SceneObjects)
		{
			obj->Tick(deltaTime);
		}

#if CY_EDITOR
		if (bIsEditorWorld)
		{
			EditorCamera->Tick(deltaTime);

			if (CurrentSelectedObject.IsValid())
			{
				if (Input::IsKeyPressed(CY_KEY_DELETE))
				{
					CurrentSelectedObject->Destroy();
				}

				if (Input::IsKeyDown(CY_KEY_LEFT_CONTROL) && Input::IsKeyPressed(CY_KEY_C))
				{
					CurrentCopiedObject = CurrentSelectedObject;
				}

				if (Input::IsKeyDown(CY_KEY_LEFT_CONTROL) && Input::IsKeyPressed(CY_KEY_D))
				{
					SceneObject* n = CreateSceneObject<SceneObject>(Vector3::Zero, Quat::Identity);
					n->Object::CopyFrom(CurrentSelectedObject.Get());
					CurrentSelectedObject = ObjectManager::GetSharedPtrTyped<SceneObject>(n).MakeWeak();
				}
			}

			if (CurrentCopiedObject.IsValid() && Input::IsKeyDown(CY_KEY_LEFT_CONTROL) && Input::IsKeyPressed(CY_KEY_V))
			{
				SceneObject* n = CreateSceneObject<SceneObject>(Vector3::Zero, Quat::Identity);
				n->Object::CopyFrom(CurrentCopiedObject.Get());
				CurrentSelectedObject = ObjectManager::GetSharedPtrTyped<SceneObject>(n).MakeWeak();
			}

			if (bIsEditorWorld)
			{
				for (auto obj : m_SceneObjects)
				{
					obj->EditorTick(deltaTime);
				}
			}
		}
#endif
	}

	void World::DestroyObject(SceneObject* obj)
	{
		ObjectManager::DestroyObject(obj);
		m_SceneObjects.Remove(obj);
	}

	Array<Component*> World::GetAllComponentsOfType(String typeName) const
	{
		const auto it = TrackedComponents.find(typeName);
		if (it != TrackedComponents.end())
		{
			return it->second;
		}
		return Array<Component*>();
	}

	Array<SceneObject*> World::GetSceneObjects() const
	{
		return m_SceneObjects;
	}

	void World::RegisterComponent(Component* component)
	{
		s_Scene->RegisterComponent_Internal(component);
	}

	void World::UnregisterComponent(Component* component)
	{
		s_Scene->UnregisterComponent_Internal(component);
	}

#if CY_EDITOR
	void World::SetIsEditorWorld()
	{
		bIsEditorWorld = true;
		// spawn editor camera
		SceneObject* cameraParent = CreateSceneObject<SceneObject>(Vector3(0, 0.5f, -4), Quat::Identity);
		cameraParent->Name = "Camera Parent";
#if 1
		EditorCamera = CreateSceneObject<SceneObject>(Vector3(0, 0.5f, -4), Quat::Identity);
		EditorCamera->Name = "Editor Camera";
#elif
		EditorCamera = ObjectManager::CreateObject<SceneObject>();
		EditorCamera->Name = "Editor Camera";
		EditorCamera->OwningWorld = ObjectManager::GetSharedPtrTyped<World>(this).MakeWeak();
		EditorCamera->GetTransform()->SetPosition(Vector3(0, 0, 0));
		EditorCamera->GetTransform()->SetScale(Vector3::One);
		EditorCamera->Start();
#endif
		EditorCamera->SetParent(cameraParent);

		EditorCameraComponent* m_Camera = EditorCamera->CreateAndAddComponent<EditorCameraComponent>();
		m_Camera->InitPerspectiveCamera({ 45.0f, 1280, 720, 0.1f, 150.0f });
	}
#endif

	void World::RegisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Registering component of type {0}", *component->GetClass()->Name);
		const String _id = component->GetClass()->Name;
		if (TrackedComponents.find(_id) == TrackedComponents.end())
			TrackedComponents[_id] = {};
		TrackedComponents[_id].Emplace(component);
	}

	void World::UnregisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Unregistering component of type {0}", *component->GetClass()->Name);
		const String _id = component->GetClass()->Name;
		TrackedComponents[_id].Remove(component);
	}
}
