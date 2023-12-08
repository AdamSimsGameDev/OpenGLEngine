#pragma once

#include "CyEngine/Core.h"
#include "Layer.h"
#include "EditorTab.h"
#include <CyEngine/Renderer/FrameBuffer.h>

namespace Cy
{
	class ViewportTab;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;

		void PushTab(EditorTab* tab);
		void PopTab(unsigned int id);

		template<typename T>
		T* FindTab() const
		{
			for (auto& tab : m_Tabs)
			{
				if (T* t = Cast<T>(tab.second))
				{
					return t;
				}
			}
			return nullptr;
		}

		FrameBuffer* GetFrameBuffer() const { return m_FrameBuffer.get(); }

		static EditorLayer& Get() { return *s_Instance; }

	protected:
		virtual void OnImGuiRender() override;
		virtual void OnUpdate(float deltaTime) override;

	private:
		bool m_ShowDemo = false;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		std::unordered_map<unsigned int, EditorTab*> m_Tabs;

		ViewportTab* m_ViewportTab;

		static EditorLayer* s_Instance;
	};
}
