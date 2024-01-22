#include "../ui.h"


namespace celosia::render {
	void groupbox_body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title, const std::string description) {
		// use theme_variables
		ImColor a(255, 41, 73, 255);
		ImColor b(208, 179, 255, 255);

		// full style
		drawlist->AddRectFilled(ImVec2(offset.x, offset.y + (style::groupbox::height / 2)), offset_max, style::themes::active.background_darker, style::general::rounding);
		render::AddRectFilledMultiColorRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), a, b, 4);

		// minimal style
		//render::AddRectFilledHalfRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), ImColor(4, 4, 4, 255), 4);
		//drawlist->AddRectFilledMultiColor(ImVec2(offset.x, offset.y + (style::groupbox::height) - 2), ImVec2(offset_max.x, offset.y + (style::groupbox::height)), a, b, b, a); // ctodo: make a func of this
	}

	void groupbox_begin(const std::string title, const std::string description) {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();

		ImVec2 offset = {
			style::sidebar::width + style::frame::size_padding.x,
			style::titlebar::height + style::frame::size_padding.y
		};

		ImVec2 offset_max = {
			ui::size.x - style::frame::size_padding.x,
			ui::size.y - style::frame::size_padding.y
		};

		ImVec2 offset_available = {
			offset_max.x - style::sidebar::width - style::frame::size_padding.x,
			offset_max.y - style::titlebar::height - style::frame::size_padding.y
		};

		groupbox_body(drawlist_window, offset, offset_max, "", "");

		ImGui::SetCursorPos(ImVec2(offset.x + style::groupbox::padding, offset.y + style::groupbox::height + style::groupbox::padding));
		ImGui::BeginChild(title.c_str(), ImVec2(offset_available.x - style::groupbox::padding, offset_available.y - style::groupbox::height - style::groupbox::padding));
	}

	void groupbox_end() { // this is required and cannot be done in the same code as begin because the components will not be defined until after, which would not work
		ImGui::EndChild();
	}
}
