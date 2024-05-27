#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class SceneObject;
	class World;
	class Texture;

	class OutlinerTab : public EditorTab
	{
	public:
		OutlinerTab()
			: EditorTab("Outliner") {}

		virtual void OnRender() override;

	protected:
		void RenderTree(World* world, const Array<SceneObject*>& objects, SceneObject*& currentItem, bool isRoot = false);

	private:
		WeakPtr<SceneObject> ContextMenuObject;
	};
}

