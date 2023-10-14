#pragma once

#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class OutputTab : public EditorTab
	{
	public:		
		OutputTab();
		virtual void OnRender() override;

	private:
		bool m_ShouldAutoScroll = true;
		char m_FilterBuffer[256];
		String m_Filter;
	};
}
