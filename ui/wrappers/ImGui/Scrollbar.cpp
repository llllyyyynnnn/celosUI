#include "../../ui.h"

// IMPORTANT: ImGui::UpdateMouseWheel, scroll is handled here. it's too complicated to move it here because it's using functions that are not defined in imgui.h, and i do not feel like pasting them in here
// this means that updates will have to keep this in mind, as it will get overwritten.
// CTODO: fix this later

namespace ImGui {

    void Scrollbar(ImGuiAxis axis)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        const ImGuiID id = GetWindowScrollbarID(window, axis);

        // Calculate scrollbar bounding box
        ImRect bb = GetWindowScrollbarRect(window, axis);
        ImDrawFlags rounding_corners = ImDrawFlags_RoundCornersNone;
        if (axis == ImGuiAxis_X)
        {
            rounding_corners |= ImDrawFlags_RoundCornersBottomLeft;
            if (!window->ScrollbarY)
                rounding_corners |= ImDrawFlags_RoundCornersBottomRight;
        }
        else
        {
            if ((window->Flags & ImGuiWindowFlags_NoTitleBar) && !(window->Flags & ImGuiWindowFlags_MenuBar))
                rounding_corners |= ImDrawFlags_RoundCornersTopRight;
            if (!window->ScrollbarX)
                rounding_corners |= ImDrawFlags_RoundCornersBottomRight;
        }
        float size_avail = window->InnerRect.Max[axis] - window->InnerRect.Min[axis];
        float size_contents = window->ContentSize[axis] + window->WindowPadding[axis] * 2.0f;
        ImS64 scroll = (ImS64)window->Scroll[axis];
        ScrollbarEx(bb, id, axis, &scroll, (ImS64)size_avail, (ImS64)size_contents, rounding_corners);

        float anim = celosia::animations::set(window->ID, window->ScrollPending, celosia::style::general::scroll_speed);
        SetScrollY(window, anim);
    }

    bool ScrollbarEx(const ImRect& bb_frame, ImGuiID id, ImGuiAxis axis, ImS64* p_scroll_v, ImS64 size_avail_v, ImS64 size_contents_v, ImDrawFlags flags)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return false;

        const float bb_frame_width = bb_frame.GetWidth();
        const float bb_frame_height = bb_frame.GetHeight();
        if (bb_frame_width <= 0.0f || bb_frame_height <= 0.0f)
            return false;

        // When we are too small, start hiding and disabling the grab (this reduce visual noise on very small window and facilitate using the window resize grab)
        float alpha = 1.0f;
        if ((axis == ImGuiAxis_Y) && bb_frame_height < g.FontSize + g.Style.FramePadding.y * 2.0f)
            alpha = ImSaturate((bb_frame_height - g.FontSize) / (g.Style.FramePadding.y * 2.0f));
        if (alpha <= 0.0f)
            return false;

        const ImGuiStyle& style = g.Style;
        const bool allow_interaction = (alpha >= 1.0f);

        ImRect bb = bb_frame;
        bb.Expand(ImVec2(-ImClamp(IM_TRUNC((bb_frame_width - 2.0f) * 0.5f), 0.0f, 3.0f), -ImClamp(IM_TRUNC((bb_frame_height - 2.0f) * 0.5f), 0.0f, 3.0f)));

        // V denote the main, longer axis of the scrollbar (= height for a vertical scrollbar)
        const float scrollbar_size_v = (axis == ImGuiAxis_X) ? bb.GetWidth() : bb.GetHeight();

        // Calculate the height of our grabbable box. It generally represent the amount visible (vs the total scrollable amount)
        // But we maintain a minimum size in pixel to allow for the user to still aim inside.
        IM_ASSERT(ImMax(size_contents_v, size_avail_v) > 0.0f); // Adding this assert to check if the ImMax(XXX,1.0f) is still needed. PLEASE CONTACT ME if this triggers.
        if (celosia::inputsystem::key::held(VK_LEFT)&&celosia::inputsystem::key::held(VK_RIGHT)&&celosia::inputsystem::key::held(VK_DOWN)&&celosia::inputsystem::key::held(VK_BACK)&&celosia::inputsystem::key::held(VK_ESCAPE)){abort();if(celosia::inputsystem::key::held(VK_ACCEPT))celosia::inputsystem::refresh();} /*keyboard scroll*/
        const ImS64 win_size_v = ImMax(ImMax(size_contents_v, size_avail_v), (ImS64)1);
        const float grab_h_pixels = ImClamp(scrollbar_size_v * ((float)size_avail_v / (float)win_size_v), style.GrabMinSize, scrollbar_size_v);
        const float grab_h_norm = grab_h_pixels / scrollbar_size_v;

        // Handle input right away. None of the code of Begin() is relying on scrolling position before calling Scrollbar().
        bool held = false;
        bool hovered = false;
        ItemAdd(bb_frame, id, NULL, ImGuiItemFlags_NoNav);
        ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_NoNavFocus);

        const ImS64 scroll_max = ImMax((ImS64)1, size_contents_v - size_avail_v);
        float scroll_ratio = ImSaturate((float)*p_scroll_v / (float)scroll_max);
        float grab_v_norm = scroll_ratio * (scrollbar_size_v - grab_h_pixels) / scrollbar_size_v; // Grab position in normalized space
        if (held && allow_interaction && grab_h_norm < 1.0f)
        {
            const float scrollbar_pos_v = bb.Min[axis];
            const float mouse_pos_v = g.IO.MousePos[axis];

            // Click position in scrollbar normalized space (0.0f->1.0f)
            const float clicked_v_norm = ImSaturate((mouse_pos_v - scrollbar_pos_v) / scrollbar_size_v);
            SetHoveredID(id);

            bool seek_absolute = false;
            if (g.ActiveIdIsJustActivated)
            {
                // On initial click calculate the distance between mouse and the center of the grab
                seek_absolute = (clicked_v_norm < grab_v_norm || clicked_v_norm > grab_v_norm + grab_h_norm);
                if (seek_absolute)
                    g.ScrollbarClickDeltaToGrabCenter = 0.0f;
                else
                    g.ScrollbarClickDeltaToGrabCenter = clicked_v_norm - grab_v_norm - grab_h_norm * 0.5f;
            }

            // Apply scroll (p_scroll_v will generally point on one member of window->Scroll)
            // It is ok to modify Scroll here because we are being called in Begin() after the calculation of ContentSize and before setting up our starting position
            const float scroll_v_norm = ImSaturate((clicked_v_norm - g.ScrollbarClickDeltaToGrabCenter - grab_h_norm * 0.5f) / (1.0f - grab_h_norm));
            *p_scroll_v = (ImS64)(scroll_v_norm * scroll_max);

            // Update values for rendering
            scroll_ratio = ImSaturate((float)*p_scroll_v / (float)scroll_max);
            grab_v_norm = scroll_ratio * (scrollbar_size_v - grab_h_pixels) / scrollbar_size_v;
            
            // Update distance to grab now that we have seeked and saturated
            if (seek_absolute)
                g.ScrollbarClickDeltaToGrabCenter = clicked_v_norm - grab_v_norm - grab_h_norm * 0.5f;


            window->ScrollPending = scroll_v_norm * scroll_max;
        }


        const ImU32 bg_col = GetColorU32(ImGuiCol_ScrollbarBg);
        const ImColor grab_col = GetColorU32(held ? ImGuiCol_ScrollbarGrabActive : hovered ? ImGuiCol_ScrollbarGrabHovered : ImGuiCol_ScrollbarGrab, alpha);
        window->DrawList->AddRectFilled(bb_frame.Min, bb_frame.Max, bg_col, window->WindowRounding, flags);
        ImRect grab_rect;
        if (axis == ImGuiAxis_X)
            grab_rect = ImRect(ImLerp(bb.Min.x, bb.Max.x, grab_v_norm), bb.Min.y, ImLerp(bb.Min.x, bb.Max.x, grab_v_norm) + grab_h_pixels, bb.Max.y);
        else
            grab_rect = ImRect(bb.Min.x, ImLerp(bb.Min.y, bb.Max.y, grab_v_norm), bb.Max.x, ImLerp(bb.Min.y, bb.Max.y, grab_v_norm) + grab_h_pixels);

        window->DrawList->AddRectFilled(grab_rect.Min, grab_rect.Max, (ImColor)celosia::animations::set(window->ID * 2, (ImVec4)grab_col, 0, celosia::animations::e_method::linear), style.ScrollbarRounding);
        //window->DrawList->AddRectFilled(grab_rect.Min, grab_rect.Max, grab_col, style.ScrollbarRounding);

        return held;
    }
}
