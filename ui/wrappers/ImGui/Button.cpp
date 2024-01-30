#include "../../ui.h"

void style1(const ImRect bb, const char* label, ImVec2 label_size, const ImGuiStyle& style, ImColor col) {
    ImGui::RenderFrameAnimated(label, bb.Min, bb.Max, celosia::style::themes::rgb_intensity(col, 0.75), true, style.FrameRounding);
    ImGui::RenderFrameBorderAnimated(label, bb.Min, bb.Max, col, style.FrameRounding);
    ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label, NULL, &label_size, style.ButtonTextAlign, &bb);
}

namespace ImGui {
    bool ButtonEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags) // ctodo: maybe define Button here as well, incase it gets updated & this one becomes invalid
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;
        if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
        ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        const ImColor col = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        RenderNavHighlight(bb, id);
        style1(bb, label, label_size, style, col);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }
}