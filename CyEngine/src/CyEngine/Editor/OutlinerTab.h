#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class OutlinerTab : public EditorTab
	{
	public:
		OutlinerTab()
			: EditorTab("Outliner") {}

		virtual void OnRender() override;
	};
}

