#pragma once

namespace celosia::render {
	inline ImGuiIO* io = nullptr;
	inline ImDrawList* drawlist_foreground = nullptr;
	inline ImDrawList* drawlist_background = nullptr;

	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding);
	void titlebar();
	void sidebar();
	void begingroupbox(std::string title, std::string description = "");
	void endgroupbox();
}