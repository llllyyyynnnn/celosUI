#include "../../ui.h"

void RenderCheckMarkAnimated(bool active, const char* label, ImDrawList* drawlist, ImRect check_bb, float pad, float square_sz, ImColor clr) {
    ImColor check_col = celosia::style::general::main_color;

    if (!active)
        check_col = clr;

    ImColor animated = (ImColor)celosia::animations::set(label, (ImVec4)check_col, 0.f, celosia::animations::e_method::linear);

    ImGui::RenderCheckMark(drawlist, check_bb.Min + ImVec2(pad, pad), animated, square_sz - pad * 2.0f);
    ImGui::RenderFrameBorderColor(check_bb.Min, check_bb.Max, animated,4.f);
    
}

namespace ImGui {
    bool Checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float square_sz = GetFrameHeight() / 2;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y));
        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }

        bool hovered, held;
        bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        RenderNavHighlight(total_bb, id);
        //RenderFrame(check_bb.Min, check_bb.Max, , true, style.FrameRounding);
        //RenderFrameBorderAnimated(label, check_bb.Min, check_bb.Max, clr, true, style.FrameRounding);

        bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;
        if (mixed_value)
        {
            // Undocumented tristate/mixed/indeterminate checkbox (#2644)
            // This may seem awkwardly designed because the aim is to make ImGuiItemFlags_MixedValue supported by all widgets (not just checkbox)
            ImVec2 pad(ImMax(1.0f, IM_TRUNC(square_sz / 3.6f)), ImMax(1.0f, IM_TRUNC(square_sz / 3.6f)));
           // window->DrawList->AddRectFilled(check_bb.Min + pad, check_bb.Max - pad, check_col, style.FrameRounding);
        }

        ImColor clr = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        const float pad = ImMax(1.0f, IM_TRUNC(square_sz / 6.0f));
        RenderCheckMarkAnimated(*v, label, window->DrawList, check_bb, pad, square_sz, clr);

        ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y /*+ style.FramePadding.y*/);
        if (g.LogEnabled)
            LogRenderedText(&label_pos, mixed_value ? "[~]" : *v ? "[x]" : "[ ]");
        if (label_size.x > 0.0f)
            RenderText(label_pos, label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return pressed;
    }
}