#pragma once

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Objects/SceneObject.h"
#include "generated/CubeObject.gen.h"

namespace Cy
{
	CLASS()
	class CubeObject : public SceneObject
	{
		GENERATED_CLASS(CubeObject)

	public:
		CubeObject();

		PROPERTY()
		Array<int> TestArr;

	private:
		MeshComponent* m_MeshComponent;
	};
}

