#include "cypch.h"
#include "ClassLibrary.h"

#include "Component.gen.h"
#include "MeshComponent.gen.h"
#include "SceneObject.gen.h"
#include "Transform.gen.h"
#include "CameraObject.gen.h"
#include "CubeObject.gen.h"
#include "Object.gen.h"
#include "PlaneObject.gen.h"


namespace Cy
{
	std::unordered_map<std::string, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =
	{
		{ "Component", &ComponentClass::Get },
{ "MeshComponent", &MeshComponentClass::Get },
{ "SceneObject", &SceneObjectClass::Get },
{ "Transform", &TransformClass::Get },
{ "CameraObject", &CameraObjectClass::Get },
{ "CubeObject", &CubeObjectClass::Get },
{ "Object", &ObjectClass::Get },
{ "PlaneObject", &PlaneObjectClass::Get },

	};
}

