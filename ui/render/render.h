#pragma once

namespace celosia::render {
	inline ImGuiIO* io = nullptr;
	inline ImDrawList* drawlist_foreground = nullptr;
	inline ImDrawList* drawlist_background = nullptr;

	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding);
	void AddRectFilledHalfRounded(ImDrawList* drawlist, const ImVec2& min, const ImVec2& max, const ImColor& clr, const int& rounding);

	void titlebar();
	void sidebar();

	void groupbox_body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title = "", const std::string description = "");
	void groupbox_begin(const std::string title, const std::string description = "");
	void groupbox_end();
}