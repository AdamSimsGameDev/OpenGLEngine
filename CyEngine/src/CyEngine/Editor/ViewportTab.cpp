#include "cypch.h"
#include "ViewportTab.h"

namespace Cy
{
	ViewportTab::ViewportTab()
		: EditorTab("Viewport")
	{
	}

	void ViewportTab::OnRender()
	{
		if (!m_FrameBuffer)
		{
			return;
		}

		if (ImGui::Begin("Viewport", &m_TabOpen))
		{
			ImVec2 newSize = ImGui::GetContentRegionAvail();
			uint32_t textureId = m_FrameBuffer->GetColorAttachmentRendererId();
			ImGui::Image((void*)textureId, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

			if (m_ViewportSize.x != newSize.x || m_ViewportSize.y != newSize.y)
			{
				m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				m_ViewportSize = newSize;
			}
		}

		ImGui::End();
	}
	
	void ViewportTab::SetFrameBuffer(std::shared_ptr<FrameBuffer> inBuffer)
	{
		m_FrameBuffer = inBuffer;
	}
}
