#pragma once

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	class CubeObject : public SceneObject
	{
		GENERATE_OBJECT(CubeObject);

	public:
		CubeObject();

	private:
		MeshComponent* m_MeshComponent;
	};
}

