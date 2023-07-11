#pragma once

#include "Layer.h"
#include "EditorTab.h"

namespace Cy
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		void PushTab(EditorTab* tab);
		void PopTab(unsigned int id);

		static EditorLayer& Get() { return *s_Instance; }

	protected:
		virtual void OnImGuiRender() override;

	private:
		bool m_ShowDemo = false;

		std::unordered_map<unsigned int, EditorTab*> m_Tabs;

		static EditorLayer* s_Instance;
	};
}
