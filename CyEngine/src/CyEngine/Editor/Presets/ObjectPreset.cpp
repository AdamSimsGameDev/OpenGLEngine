#include "cypch.h"
#include "ObjectPreset.h"
#include "CyEngine/Components/MeshComponent.h"

namespace Cy
{
    std::unordered_map<String, ObjectPresetBase*> ObjectPresetBase::ObjectPresets;

    DEFINE_OBJECT_PRESET(ObjectPresetCube, Cube);
    Object* ObjectPresetCube::SpawnObject(World* World) const
    {
        SceneObject* Obj = World->CreateSceneObject<SceneObject>(Vector3(0, 0, 0), Quat::Identity);
        Obj->SetName( "New Cube" );

        MeshComponent* Mesh = Obj->CreateAndAddComponent<MeshComponent>();
        Mesh->SetMeshType( MeshComponentType::Cube );

        return Obj;
    }

    DEFINE_OBJECT_PRESET( ObjectPresetSphere, Sphere );
    Object* ObjectPresetSphere::SpawnObject( World* World ) const
    {
        SceneObject* Obj = World->CreateSceneObject<SceneObject>( Vector3( 0, 0, 0 ), Quat::Identity );
        Obj->SetName( "New Sphere" );

        MeshComponent* Mesh = Obj->CreateAndAddComponent<MeshComponent>();
        Mesh->SetMeshType( MeshComponentType::Sphere );

        return Obj;
    }
}