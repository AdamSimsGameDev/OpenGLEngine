#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>

namespace Cy
{
	void InspectorTab::OnRender()
	{
		ImGui::Begin("Inspector", &m_TabOpen);

		ImGui::End();
	}
}
