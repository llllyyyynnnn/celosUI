#include "../../ui.h"

void tabstyle(const ImRect bb, const char* label, ImVec2 label_size, const ImGuiStyle& style, ImColor col) {
    if (celosia::variables::temporary::strings["tab_active"] == label)
        col = celosia::style::general::main_color;

    ImGui::RenderFrameBorderAnimated(label, bb.Min, bb.Max, col, true, style.FrameRounding);
    ImGui::RenderTextClipped(ImVec2(bb.Min.x + style.FramePadding.x, bb.Min.y + style.FramePadding.y), ImVec2(bb.Max.x - style.FramePadding.x, bb.Max.y - style.FramePadding.y), label, NULL, &label_size, style.ButtonTextAlign, &bb);
}

namespace ImGui { 
    bool TabButton(const char* label)
    {
        return TabButtonEx(label, ImGuiButtonFlags_None);
    }
	bool TabButtonEx(const char* label, ImGuiButtonFlags flags) {
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
        //ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
        ImVec2 size = {celosia::style::sidebar::width - style.FramePadding.x * 2, label_size.y + style.FramePadding.y * 2.0f };
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        if(pressed) 
            celosia::variables::temporary::strings["tab_active"] = label; // change tab

        const ImColor col = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        RenderNavHighlight(bb, id);
        tabstyle(bb, label, label_size, style, col);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
	}
}