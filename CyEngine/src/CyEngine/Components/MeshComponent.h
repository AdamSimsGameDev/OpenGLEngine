#pragma once
#include "Component.h"
#include "generated/MeshComponent.gen.h"

namespace Cy
{
    class Mesh;
    class Shader;
    class Texture;

    ENUM()
    enum class MeshComponentType : uint8_t
    {
        Cube,
        Sphere,
        Plane,
        Custom
    };

    CLASS(EditorSpawnable)
    class MeshComponent : public Component
    {
        GENERATED_CLASS(MeshComponent)

        friend class Renderer;

    public:
        virtual void Start() override;

        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        Mesh* GetMesh() const { return m_Mesh; }

        Shader* GetShader() const { return m_Shader; }
        void SetShader(Shader* shader) { m_Shader = shader; }

        void SetMeshType(MeshComponentType type);

        PROPERTY()
        bool bIsVisible = true;

        PROPERTY()
        MeshComponentType Type;

    protected:
#if CY_EDITOR
        virtual void EditorTick(float deltaTime) override;

        MeshComponentType LastType;
#endif

        static Mesh CubeMesh;
        static Mesh SphereMesh;
        static Mesh PlaneMesh;

    private:
        Texture* m_Texture;

        PROPERTY()
        Shader* m_Shader;

        PROPERTY()
        Mesh* m_Mesh;
    };
}
