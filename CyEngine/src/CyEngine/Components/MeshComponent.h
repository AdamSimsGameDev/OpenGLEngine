#pragma once
#include "Component.h"
#include "generated/MeshComponent.gen.h"

namespace Cy
{
    class Mesh;
    class Shader;

    enum class MeshComponentType : uint8_t
    {
        Cube
    };

    CLASS()
    class MeshComponent : public Component
    {
        GENERATED_CLASS(MeshComponent)

        friend class Renderer;

    public:
        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        Mesh* GetMesh() const { return m_Mesh; }

        Shader* GetShader() const { return m_Shader; }
        void SetShader(Shader* shader) { m_Shader = shader; }

        PROPERTY()
        bool bIsVisible = true;

        PROPERTY()
        MeshComponentType Type;

    private:
        Shader* m_Shader;
        Mesh* m_Mesh;
    };
}
