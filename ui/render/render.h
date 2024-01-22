#pragma once

namespace celosia::render {
	inline ImGuiIO* io = nullptr;
	inline ImDrawList* drawlist_foreground = nullptr;
	inline ImDrawList* drawlist_background = nullptr;

	void titlebar();
	void sidebar();
	void groupbox(std::string title, std::string description = "");
}