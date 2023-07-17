#pragma once

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	class CubeObject : public SceneObject
	{
	public:
		CubeObject();

		virtual std::string ClassName() const override { return "CubeObject"; }

	private:
		MeshComponent* m_MeshComponent;
	};
}

