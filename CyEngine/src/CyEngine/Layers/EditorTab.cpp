#include "cypch.h"
#include "EditorTab.h"
#include "EditorLayer.h"
#include <imgui.h>

namespace Cy
{
	unsigned int EditorTab::s_NextId = 0;

	EditorTab::EditorTab(String name, ImGuiWindowFlags flags)
	{
		m_DebugName = name;

		m_TabClosing = false;

		WindowFlags = flags;

		m_TabId = s_NextId;
		s_NextId++;
	
		CY_CORE_TRACE("Created EditorTab {0}", *m_DebugName);
	}

	void EditorTab::Close()
	{
		m_TabClosing = true;
	}
}