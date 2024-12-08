#include "cypch.h"
#include "ImGuiExtension.h"
#include <imgui.h>
#include <imgui_internal.h>

void ImGui::CenterHorizontally(float width)
{
	const float avail = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (avail / 2.0f) - (width / 2.0f));
}
