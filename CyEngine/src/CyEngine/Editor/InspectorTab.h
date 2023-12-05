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

		bool RenderProperty(void* obj, const Class* objectClass, const String& prefix, const std::pair<String, ClassProperty>& prop);
		void RenderObject(void* obj, const Class* cl, bool showHeader);
		void RenderObjectClass(void* obj, const Class* cl, bool showHeader);
		virtual void OnRender() override;
	};
}
