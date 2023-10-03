#pragma once
#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Objects/SceneObject.h"
#include "generated/PlaneObject.gen.h"

namespace Cy
{
	CLASS()
	class PlaneObject : public SceneObject
	{
		GENERATED_CLASS(PlaneObject)

	public:
		PlaneObject();

	private:
		MeshComponent* m_MeshComponent;
	};
}

