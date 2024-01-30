#include "../../../ui.h"
#include "../../../ui.h"

void ImGui::RenderFrameBorderAnimated(const char* label, ImVec2 p_min, ImVec2 p_max, ImColor fill_col, float rounding) // any component using this will be animated with no need for any further setup
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;


    std::string std_label = (std::string)label;
    std::string name = "RenderFrameBorderAnimated";
    ImColor animated_color = celosia::animations::set(std_label + name, ImVec4(fill_col), 0.f, celosia::animations::e_method::linear);

    int border_size = celosia::style::frame::border_size;
    //window->DrawList->AddRect(p_min + ImVec2(1, 1), p_max + ImVec2(1, 1), animated_color, rounding, 0, border_size);
    window->DrawList->AddRect(p_min, p_max, animated_color, rounding, 0, border_size);
}