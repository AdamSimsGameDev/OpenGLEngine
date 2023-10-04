#pragma once

#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class InspectorTab : public EditorTab
	{
	public:
		InspectorTab()
			: EditorTab("Inspector") {}

		bool RenderProperty(Object* obj, const std::string& prefix, const std::pair<std::string, ClassProperty>& prop);
		void RenderObject(Object* obj);
		void RenderObjectClass(Object* obj, const Class* cl, std::string prefix = "");
		virtual void OnRender() override;
	};
}
