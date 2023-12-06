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

#if CY_EDITOR
		virtual void EditorTick(float deltaTime);
#endif

		class SceneObject* GetOwner() const;
	};
}