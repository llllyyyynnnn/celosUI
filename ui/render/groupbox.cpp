#include "../ui.h"

namespace celosia::render::groupbox {
	void body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title, const std::string description, e_group_layout layout) {
		// use theme_variables
		ImColor a = style::general::main_color;
		ImColor b = style::themes::get_accent(a);

		drawlist->AddRectFilled(ImVec2(offset.x, offset.y + (style::groupbox::height / 2)), offset_max, style::themes::active.background_darker, style::general::rounding);

		if (style::themes::active.tab_style == style::themes::e_tab_title_style::full) {
			ImGui::AddRectFilledMultiColorRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), a, b, 4);
			return;
		}

		if (style::themes::active.tab_style == style::themes::e_tab_title_style::minimal) {
			ImGui::AddRectFilledHalfRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), ImColor(8, 8, 8, 255), 4);
			drawlist->AddRectFilledMultiColor(ImVec2(offset.x, offset.y + (style::groupbox::height)-2), ImVec2(offset_max.x, offset.y + (style::groupbox::height)), a, b, b, a); // ctodo: make a func of this
			return;
		}
	}

	void begin(const std::string title, const std::string description, e_group_layout layout) {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		float active_spacing = animations::str_map["groupbox_active_spacing"]; // for tab switching animations

		ImVec2 offset = {
			style::sidebar::width + style::frame::size_padding.x,
			style::titlebar::height + style::frame::size_padding.y + active_spacing
		};

		ImVec2 offset_max = {
			ui::size.x - style::frame::size_padding.x,
			ui::size.y - style::frame::size_padding.y + active_spacing
		};

		ImVec2 offset_available = {
			offset_max.x - style::sidebar::width - style::frame::size_padding.x,
			offset_max.y - style::titlebar::height - style::frame::size_padding.y
		};

		body(drawlist_window, offset, offset_max, title, description, layout);

		ImGui::SetCursorPos(ImVec2(offset.x + style::groupbox::padding, offset.y + style::groupbox::height + style::groupbox::padding));
		ImGui::BeginChild(title.c_str(), ImVec2(offset_available.x - style::groupbox::padding, offset_available.y - style::groupbox::height - style::groupbox::padding));
	}

	void end() { // this is required and cannot be done in the same code as begin because the components will not be defined until after, which would not work
		ImGui::EndChild();
	}
}

// ctodo: auto layout (store amount of calls, perform later)

/* dark / white text
const float combined_rgb = dUI::variables::menu::colors::theme.Value.x + dUI::variables::menu::colors::theme.Value.y + dUI::variables::menu::colors::theme.Value.z;
	float text_color_goal;

	if (combined_rgb > 2.f)
		text_color_goal = 0.15686f;
	else
		text_color_goal = 1.f;

	const float text_color_fl = anim::smooth("Groupbox Text Color", text_color_goal, 1.f);
	ImColor text_color = ImColor(text_color_fl, text_color_fl, text_color_fl, alpha);
*/
