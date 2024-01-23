#pragma once

namespace celosia::render {
	inline ImGuiIO* io = nullptr;
	inline ImDrawList* drawlist_foreground = nullptr;
	inline ImDrawList* drawlist_background = nullptr;


	void titlebar();
	void sidebar();

	namespace text {
		void font(const char* text, ImFont* font);
		void shadow(const char* text, ImFont* font);
	}

	namespace groupbox {
		enum e_group_layout { fullscreen, two, four };
		void body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title = "", const std::string description = "", e_group_layout layout = e_group_layout::two);
		void begin(const std::string title, const std::string description = "", e_group_layout layout = e_group_layout::two);
		void end();
	}
}