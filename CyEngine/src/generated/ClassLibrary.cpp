#include "cypch.h"
#include "ClassLibrary.h"

#include "MeshComponent.gen.h"
#include "Component.gen.h"
#include "CameraObject.gen.h"
#include "CubeObject.gen.h"
#include "Object.gen.h"
#include "PlaneObject.gen.h"
#include "SceneObject.gen.h"
#include "Scene.gen.h"
#include "Transform.gen.h"


namespace Cy
{
	std::unordered_map<std::string, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =
	{
		{ "MeshComponent", &MeshComponentClass::Get },
{ "Component", &ComponentClass::Get },
{ "CameraObject", &CameraObjectClass::Get },
{ "CubeObject", &CubeObjectClass::Get },
{ "Object", &ObjectClass::Get },
{ "PlaneObject", &PlaneObjectClass::Get },
{ "SceneObject", &SceneObjectClass::Get },
{ "Scene", &SceneClass::Get },
{ "Transform", &TransformClass::Get },

	};
}

