#include "cypch.h"
#include "OutputTab.h"
#include "CyEngine/Layers/EditorLayer.h"

#include <algorithm> 
#include <cctype>
#include <locale>
#include <imgui.h>

namespace Cy
{
    OutputTab::OutputTab()
        : EditorTab("Output")
    {
        memset(m_FilterBuffer, 0, sizeof(m_FilterBuffer));
    }

	void OutputTab::OnRender()
	{
        if (ImGui::Begin("Output", &m_TabOpen))
        {
            if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -24), false, ImGuiWindowFlags_HorizontalScrollbar))
            {
                m_ShouldAutoScroll = ImGui::GetScrollY() == ImGui::GetScrollMaxY();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

                for (const String& v : Log::GetLast(128))
                {
                    if (m_Filter.Length() != 0)
                    {
                        if (!v.Contains(*m_Filter))
                            continue;
                    }

                    if (v.Contains("[trace]"))
                    {
                        // draw cyan text
                        ImGui::TextColored(ImVec4(0.f, 1.f, 1.f, 1.f), *v);
                    }
                    else if (v.Contains("[info]"))
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 1.f), *v);
                    }
                    else if (v.Contains("[warning]"))
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), *v);
                    }
                    else if (v.Contains("[error]"))
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), *v);
                    }
                }

                ImGui::PopStyleVar();

                if (m_ShouldAutoScroll)
                    ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();

            ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EscapeClearsAll;
            if (ImGui::InputText("Filter", m_FilterBuffer, IM_ARRAYSIZE(m_FilterBuffer), input_text_flags))
            {
                m_Filter = &m_FilterBuffer[0];
                String::Trim(m_Filter);
            }

            ImGui::SameLine();

            if (ImGui::Button("Clear Log"))
            {
                Log::Clear();
            }
        }

        ImGui::End();
	}
}
