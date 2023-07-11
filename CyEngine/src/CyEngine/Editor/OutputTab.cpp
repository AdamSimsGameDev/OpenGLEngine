#include "cypch.h"
#include "OutputTab.h"
#include "CyEngine/Layers/EditorLayer.h"

#include <algorithm> 
#include <cctype>
#include <locale>
#include <imgui.h>

namespace Cy
{
    // trim from start (in place)
    static inline void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string& s) {
        rtrim(s);
        ltrim(s);
    }

    // trim from start (copying)
    static inline std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }

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

                for (const std::string& v : Log::GetLast(128))
                {
                    if (m_Filter.length() != 0)
                    {
                        if (v.find(m_Filter) == std::string::npos)
                            continue;
                    }

                    if (v.find("[trace]") != std::string::npos)
                    {
                        // draw cyan text
                        ImGui::TextColored(ImVec4(0.f, 1.f, 1.f, 1.f), v.c_str());
                    }
                    else if (v.find("[info]") != std::string::npos)
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 1.f), v.c_str());
                    }
                    else if (v.find("[warning]") != std::string::npos)
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), v.c_str());
                    }
                    else if (v.find("[error]") != std::string::npos)
                    {
                        // draw white text
                        ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), v.c_str());
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
                m_Filter = std::string(&m_FilterBuffer[0]);
                trim(m_Filter);
            }

            ImGui::SameLine();

            if (ImGui::Button("Clear Log"))
            {
                Log::Clear();
            }

            ImGui::End();
        }
        else
        {
            ImGui::End();
        }
	}
}
