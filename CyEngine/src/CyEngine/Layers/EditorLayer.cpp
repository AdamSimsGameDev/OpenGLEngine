#include "cypch.h"
#include "EditorLayer.h"
#include "CyEngine/Editor/InspectorTab.h"
#include "CyEngine/Editor/OutputTab.h"
#include "CyEngine/Editor/ViewportTab.h"

#include <imgui.h>
#include <gl/GL.h>

namespace Cy
{
	EditorLayer* EditorLayer::s_Instance = nullptr;

	EditorLayer::EditorLayer()
	{
		s_Instance = this;

		PushTab(new OutputTab());
		PushTab(new InspectorTab());
		m_ViewportTab = new ViewportTab();
		PushTab(m_ViewportTab);
	}

	EditorLayer::~EditorLayer()
	{
		for (auto tab : m_Tabs)
		{
			delete tab.second;
		}
	}

	void EditorLayer::OnAttach()
	{
		FrameBufferSpec spec;
		spec.Width = 1280;
		spec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(spec);
		m_ViewportTab->SetFrameBuffer(m_FrameBuffer);
	}

	void EditorLayer::PushTab(EditorTab* tab)
	{
		unsigned int id = tab->GetId();
		if (m_Tabs[id])
		{
			CY_CORE_ERROR("Can't push a tab that already exists, id {0}, name {1}", id, tab->GetName().c_str());
			return;
		}

		// create the tab from the func
		m_Tabs[id] = tab;
	}

	void EditorLayer::PopTab(unsigned int id)
	{
		if (id >= m_Tabs.size())
		{
			CY_CORE_ERROR("Can't pop tab with invalid id {0}", id);
			return;
		}

		if (!m_Tabs[id])
		{
			CY_CORE_ERROR("Can't pop a tab that doesn't exist, id {0}, name {1}", id, m_Tabs[id]->GetName().c_str());
			return;
		}

		// remove the tab
		delete m_Tabs[id];
		m_Tabs.erase(id);
	}

	void EditorLayer::OnImGuiRender() 
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("Editor", nullptr, window_flags);
		
		ImGui::PopStyleVar(2);

		ImGui::BeginMainMenuBar();
		
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			for (auto& tab : m_Tabs)
			{
				ImGui::MenuItem(tab.second->GetName().c_str(), nullptr, &(tab.second->GetIsTabOpen()));
			}
			ImGui::Separator();
			ImGui::MenuItem("Demo", nullptr, &m_ShowDemo);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		ImGuiID dockspace_id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

		if (m_ShowDemo)
		{
			ImGui::ShowDemoWindow();
		}

		std::vector<unsigned int> to_remove;
		for (auto pair : m_Tabs)
		{
			EditorTab* tab = pair.second;
			if (!tab || !tab->IsTabOpen())
				continue;
			tab->OnRender();
		}

		ImGui::End();
	}

	void EditorLayer::OnUpdate()
	{
		m_FrameBuffer->Bind();

		m_FrameBuffer->Unbind();
	}
}
