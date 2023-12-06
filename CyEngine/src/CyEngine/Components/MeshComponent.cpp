#include "cypch.h"
#include "MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"

namespace Cy
{
    Mesh MeshComponent::CubeMesh = Mesh(
        "Cube", 
        { -0.5f, 0.5f, 0.5f,-0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, 0.5f, 0.5f,-0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,-0.5f, 0.5f, 0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,   0.5f,-0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,0.5f,-0.5f,-0.5f, -0.5f,-0.5f,-0.5f, -0.5f, 0.5f, -0.5f, }, 
		{ 0, 2, 1, 0, 3, 2,4, 6, 5,4, 7, 6,8, 10, 9,8, 11, 10,12, 14, 13,12, 15, 14,17, 18, 16,18, 19, 16,21, 22, 20,22, 23, 20 },
        { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f, 1.0f, 0.0f,0.0f, 1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f,0.0f, 0.0f, 1.0f,0.0f, 0.0f, -1.0f,0.0f, 0.0f, -1.0f,0.0f, 0.0f, -1.0f,0.0f, 0.0f, -1.0f }
    );

    void MeshComponent::SetMeshType(MeshComponentType type)
    {
        Type = type;
        switch (Type)
        {
        case MeshComponentType::Cube:
            CubeMesh.Generate();
            SetMesh(&CubeMesh);
            break;
        default:
            SetMesh(nullptr);
            break;
        }
    }

#if CY_EDITOR
    void MeshComponent::EditorTick(float deltaTime)
    {
        if (LastType != Type)
        {
            SetMeshType(Type);
            LastType = Type;
        }
    }
#endif
}
