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
			m_HasFocus = ImGui::IsWindowFocused();

			ImVec2 newSize = ImGui::GetContentRegionAvail();
			uint64_t textureId = m_FrameBuffer->GetColorAttachmentRendererId();

			if (m_AbsViewportSize.x != newSize.x || m_AbsViewportSize.y != newSize.y)
			{
				float scale = 16.0f / 9.0f;
				float scale2 = 9.0f / 16.0f;

				float val = newSize.x / 16.0f;
				float val2 = newSize.y / 9.0f;

				if (val <= val2)
				{
					m_ViewportSize = ImVec2(newSize.x, newSize.x * scale2);
				}
				else
				{
					m_ViewportSize = ImVec2(newSize.y * scale, newSize.y);
				}

				m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

				m_AbsViewportSize = newSize;
			}

			float _x = (m_AbsViewportSize.x - m_ViewportSize.x) * 0.5f;
			float _y = (m_AbsViewportSize.y - m_ViewportSize.y) * 0.5f;
			ImGui::SetCursorPosX(_x);
			ImGui::SetCursorPosY(_y + 26.0f);
			ImGui::Image((ImTextureID)textureId, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
		}

		ImGui::End();
	}
	
	void ViewportTab::SetFrameBuffer(std::shared_ptr<FrameBuffer> inBuffer)
	{
		m_FrameBuffer = inBuffer;
	}
}
