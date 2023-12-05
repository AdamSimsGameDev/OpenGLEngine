#include "cypch.h"
#include "ClassLibrary.h"

#include "MeshComponent.gen.h"
#include "CameraComponent.gen.h"
#include "Component.gen.h"
#include "CubeObject.gen.h"
#include "Object.gen.h"
#include "PlaneObject.gen.h"
#include "SceneObject.gen.h"
#include "Scene.gen.h"
#include "Transform.gen.h"


namespace Cy
{
	std::unordered_map<String, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =
	{
		{ "MeshComponent", &MeshComponentClass::Get },
{ "CameraComponent", &CameraComponentClass::Get },
{ "Component", &ComponentClass::Get },
{ "CubeObject", &CubeObjectClass::Get },
{ "Object", &ObjectClass::Get },
{ "PlaneObject", &PlaneObjectClass::Get },
{ "SceneObject", &SceneObjectClass::Get },
{ "Scene", &SceneClass::Get },
{ "Transform", &TransformClass::Get },

	};
}

