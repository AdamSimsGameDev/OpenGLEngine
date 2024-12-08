#include "cypch.h"
#include "ObjectSelectorTab.h"
#include "CyEngine/AssetManager/AssetManager.h"
#include "CyEngine/AssetManager/AssetInfo.h"
#include "CyEngine/Layers/EditorLayer.h"
#include "CyEngine/Textures/Texture.h"
#include "CyEngine/ImGuiExtension.h"

#include <algorithm> 
#include <cctype>
#include <locale>
#include <imgui.h>
#include <imgui_internal.h>
#include <CyEngine/Objects/SceneObject.h>

namespace Cy
{
    ObjectSelectorTab::ObjectSelectorTab(const Class* assetType, Object** targetData)
        : EditorTab("Select", ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)
    {
        memset(m_FilterBuffer, 0, sizeof(m_FilterBuffer));
        TargetAssetType = assetType;
        TargetDataPtr = targetData;
    }

    void ObjectSelectorTab::OnRender()
    {
        ImGui::SetNextWindowPos(ImGui::GetMousePos(), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(350.0f, 450.0f), ImGuiCond_Once);

        if (ImGui::Begin(*GetName(), &m_TabOpen, WindowFlags))
        {
            ImGui::BeginVertical("v1");

            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);

            ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EscapeClearsAll;
            if (ImGui::InputText("##SearchAssetFilter", m_FilterBuffer, IM_ARRAYSIZE(m_FilterBuffer), input_text_flags))
            {
                m_Filter = &m_FilterBuffer[0];
                String::Trim(m_Filter);
            }

            if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -24), false, ImGuiWindowFlags_HorizontalScrollbar))
            {
                // get all of the assets of the type we want to render
                const Array<AssetInfo*> Assets = AssetManager::GetAllAssetsOfType(TargetAssetType);
                for (const auto& Asset : Assets)
                {
                    RenderAsset(Asset);
                }
            }
            ImGui::EndChild();


            float buttonWidth = 200.0f;
            ImGui::CenterHorizontally(buttonWidth);

            if (ImGui::Button("Clear", ImVec2(buttonWidth, ImGui::GetContentRegionAvail().y)))
            {
                (*TargetDataPtr) = nullptr;
                Close();
            }

            ImGui::EndVertical();
        }

        ImGui::End();
    }

    void ObjectSelectorTab::RenderAsset(Object* asset)
    {
        constexpr float Height = 50.0f;
        constexpr float IconPadding = 4.0f;

        const auto& Style = ImGui::GetStyle();

        bool pressed = ImGui::Button(*String::Format("##{0}assetbutton", *asset->GetName()), ImVec2(ImGui::GetContentRegionAvail().x, Height));

        const ImVec2& NextButtonPos = ImGui::GetCursorPos();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + IconPadding);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - Height - Style.ItemSpacing.y + IconPadding);
        ImGui::Image(0, ImVec2(Height - IconPadding * 2, Height - IconPadding * 2));

        ImGui::SameLine();

        const float textStartX = ImGui::GetCursorPosX();

        // Asset name
        ImGui::Text(*asset->GetName());

        ImGui::SameLine();

        ImGui::SetCursorPosX(textStartX);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFont()->FontSize + Style.ItemSpacing.y);

        // Asset relative path
        if (AssetInfo* Info = Cast<AssetInfo>(asset))
        {
            ImGui::Text(*Info->GetPath());
        }

        ImGui::SetCursorPos(NextButtonPos);

        if (pressed)
        {
            (*TargetDataPtr) = asset;
            Close();
        }
    }
}
