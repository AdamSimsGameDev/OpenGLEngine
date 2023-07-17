#pragma once
#include "CyEngine/Layers/EditorTab.h"
#include <CyEngine/Renderer/FrameBuffer.h>

#include <imgui.h>

namespace Cy
{
	class ViewportTab : public EditorTab
	{
	public:
		ViewportTab();
		virtual void OnRender() override;

		void SetFrameBuffer(std::shared_ptr<FrameBuffer> inBuffer);

	private:
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		ImVec2 m_ViewportSize;
		ImVec2 m_AbsViewportSize;
	};
}

