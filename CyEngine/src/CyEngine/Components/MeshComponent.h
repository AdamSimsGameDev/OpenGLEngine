#pragma once
#include "Component.h"

namespace Cy
{
    class Mesh;
    class Shader;

    class MeshComponent : public Component
    {
        GENERATE_OBJECT(MeshComponent);

        friend class Renderer;

    public:
        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        Mesh* GetMesh() const { return m_Mesh; }

        Shader* GetShader() const { return m_Shader; }
        void SetShader(Shader* shader) { m_Shader = shader; }

    private:
        Shader* m_Shader;
        Mesh* m_Mesh;
    };
}
