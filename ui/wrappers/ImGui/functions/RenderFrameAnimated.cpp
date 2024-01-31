#include "../../../ui.h"

void ImGui::RenderFrameAnimated(const char* label, ImVec2 p_min, ImVec2 p_max, ImColor fill_col, bool border, float rounding)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    std::string std_label = (std::string)label;
    
    ImColor animated_color = celosia::animations::set(std_label + "RenderFrameAnimated", ImVec4(fill_col), 0.f, celosia::animations::e_method::linear);
    window->DrawList->AddRectFilled(p_min, p_max, animated_color, rounding);
}