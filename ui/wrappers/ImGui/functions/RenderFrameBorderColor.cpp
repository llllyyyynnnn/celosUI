#include "../../../ui.h"

void ImGui::RenderFrameBorderColor(ImVec2 p_min, ImVec2 p_max, ImColor clr,float rounding)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    int border_size = celosia::style::frame::border_size;
    if (border_size > 0)
    {
/*
        window->DrawList->AddRect(p_min + ImVec2(1, 1), p_max + ImVec2(1, 1), GetColorU32(ImGuiCol_BorderShadow), rounding, 0, border_size);
*/
        window->DrawList->AddRect(p_min, p_max, clr, rounding, 0, border_size);
    }
}
