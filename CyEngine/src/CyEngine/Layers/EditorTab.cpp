#include "cypch.h"
#include "EditorTab.h"

namespace Cy
{
	unsigned int EditorTab::s_NextId = 0;

	EditorTab::EditorTab(String name)
	{
		m_DebugName = name;

		m_TabId = s_NextId;
		s_NextId++;
	
		CY_CORE_TRACE("Created EditorTab {0}", *m_DebugName);
	}
}