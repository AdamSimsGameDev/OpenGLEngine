#pragma once

namespace Cy
{
	class EditorTab
	{
	public:
		EditorTab(std::string name = "");
		virtual ~EditorTab() {}

		virtual void OnBegin() { }
		virtual void OnEnd() { }
		
		virtual void OnUpdate() { }
		virtual void OnRender() = 0;

		inline std::string GetName() const { return m_DebugName; }
		inline unsigned int GetId() const { return m_TabId; }
		inline bool IsTabOpen() const { return m_TabOpen; }
		inline bool& GetIsTabOpen() { return m_TabOpen; }

	protected:
		bool m_TabOpen;

	private:
		std::string m_DebugName;
		unsigned int m_TabId;

		static unsigned int s_NextId;
	};
}