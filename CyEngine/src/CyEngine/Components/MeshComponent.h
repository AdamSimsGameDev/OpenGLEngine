#pragma once
#include "Component.h"

namespace Cy
{
    class Mesh;

    class MeshComponent : public Component
    {
        GENERATE_OBJECT(MeshComponent);

    public:
        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        Mesh* GetMesh() const { return m_Mesh; }

    private:
        Mesh* m_Mesh;
    };
}
