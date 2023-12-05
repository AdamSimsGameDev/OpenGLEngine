#pragma once
#include "CoreMinimal.h"
#include "CyEngine/Objects/Object.h"
#include "generated/Component.gen.h"

namespace Cy
{
	CLASS()
	class Component : public Object
	{
		GENERATED_CLASS(Component);

	public:
		virtual void Start() override;
		virtual void End() override;
		virtual void Tick(float deltaTime) { }

		class SceneObject* GetOwner() const;
	};
}