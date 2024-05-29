#include "cypch.h"
#include "ClassLibrary.h"

#include "MeshComponent.gen.h"
#include "CameraComponent.gen.h"
#include "Component.gen.h"
#include "EditorCameraComponent.gen.h"
#include "LightComponent.gen.h"
#include "Object.gen.h"
#include "SceneObject.gen.h"
#include "Mesh.gen.h"
#include "Transform.gen.h"
#include "World.gen.h"


namespace Cy
{
	std::unordered_map<String, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =
	{
		{ "MeshComponent", &MeshComponentClass::Get },
{ "CameraComponent", &CameraComponentClass::Get },
{ "Component", &ComponentClass::Get },
{ "EditorCameraComponent", &EditorCameraComponentClass::Get },
{ "LightComponent", &LightComponentClass::Get },
{ "Object", &ObjectClass::Get },
{ "SceneObject", &SceneObjectClass::Get },
{ "Mesh", &MeshClass::Get },
{ "Transform", &TransformClass::Get },
{ "World", &WorldClass::Get },

	};
	std::unordered_map<String, std::unordered_map<int, String>> ClassLibrary::EnumMap =
	{
		{ "MeshComponentType", { { 0, "Cube" }, { 1, "Sphere" }, { 2, "Plane" }, { 3, "Custom" } } },{ "TextureFilterMode", { { 0, "Point" }, { 1, "Linear" } } },{ "TextureClampMode", { { 0, "Clamp" }, { 1, "Repeat" }, { 2, "Mirrored" } } },
	};
}

