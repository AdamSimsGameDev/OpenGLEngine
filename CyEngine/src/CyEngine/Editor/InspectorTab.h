#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class InspectorTab : public EditorTab
	{
	public:
		InspectorTab()
			: EditorTab("Inspector") {}

		bool RenderProperty(Object* obj, const String& prefix, const std::pair<String, ClassProperty>& prop);
		void RenderObject(Object* obj);
		void RenderObjectClass(Object* obj, const Class* cl, String prefix = "");
		virtual void OnRender() override;
	};
}
