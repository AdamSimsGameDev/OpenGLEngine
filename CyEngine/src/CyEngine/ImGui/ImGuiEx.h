#pragma once
#include <imgui_internal.h>

namespace ImGui
{
    IMGUI_API static inline ImVec2 operator+( const ImVec2& lhs, const ImVec2& rhs ) { return ImVec2( lhs.x + rhs.x, lhs.y + rhs.y ); }

    // Widgets: Combo Bullet
      // - The BeginComboBullet()/EndComboBullet() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.
    IMGUI_API bool          BeginComboBullet( const char* label, const char* preview_value, ImGuiComboFlags flags = 0 );
    IMGUI_API void          EndComboBullet();
}