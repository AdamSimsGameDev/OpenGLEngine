#pragma once
#include "Component.h"

namespace Cy
{
    class Mesh;

    class MeshComponent : public Component
    {
    public:
        void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
        Mesh* GetMesh() const { return m_Mesh; }

        virtual std::string ClassName() const override { return "MeshComponent"; }
        static std::string ClassNameStatic() { return "MeshComponent"; }

    private:
        Mesh* m_Mesh;
    };
}
