#pragma once

namespace ImGui { // add extra ImGui components here, in order to keep it all in one place
	bool TabButton(const char* label);
	bool TabButtonEx(const char* label, ImGuiButtonFlags flags);
	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding);
	void AddRectFilledHalfRounded(ImDrawList* drawlist, const ImVec2& min, const ImVec2& max, const ImColor& clr, const int& rounding);

	IMGUI_API void RenderFrameBorderColor(ImVec2 p_min, ImVec2 p_max, ImColor clr,float rounding = 0.0f);
	IMGUI_API void RenderFrameBorderAnimated(const char* label, ImVec2 p_min, ImVec2 p_max, ImColor fill_col, bool border = true, float rounding = 0.0f);
	IMGUI_API void RenderFrameAnimated(const char* label, ImVec2 p_min, ImVec2 p_max, ImColor fill_col, bool border = true, float rounding = 0.0f);
	
	IMGUI_API bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
	IMGUI_API bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);

	IMGUI_API bool Checkbox(const char* label, bool* v);
	bool CheckboxMap(const char* label);
}