#pragma once

#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class InspectorTab : public EditorTab
	{
	public:
		InspectorTab()
			: EditorTab("Inspector") {}

		void RenderObject(Object* obj);
		virtual void OnRender() override;
	};
}
