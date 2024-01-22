#pragma once

namespace celosia::render {
	inline ImGuiIO* io = nullptr;
	inline ImDrawList* drawlist_foreground = nullptr;
	inline ImDrawList* drawlist_background = nullptr;


	void titlebar();
	void sidebar();

	void groupbox_body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title = "", const std::string description = "");
	void groupbox_begin(const std::string title, const std::string description = "");
	void groupbox_end();
}