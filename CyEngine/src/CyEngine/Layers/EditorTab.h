#pragma once
#include "CyEngine/Core.h"

namespace Cy
{
	class EditorTab
	{
	public:
		EditorTab(String name = "");
		virtual ~EditorTab() {}

		virtual void OnBegin() { }
		virtual void OnEnd() { }
		
		virtual void OnUpdate() { }
		virtual void OnRender() = 0;

		inline String GetName() const { return m_DebugName; }
		inline unsigned int GetId() const { return m_TabId; }
		inline bool IsTabOpen() const { return m_TabOpen; }
		inline bool& GetIsTabOpen() { return m_TabOpen; }

		inline bool IsFocused() const { return m_HasFocus; }

	protected:
		bool m_TabOpen;
		bool m_HasFocus;

	private:
		String m_DebugName;
		unsigned int m_TabId;

		static unsigned int s_NextId;
	};
}