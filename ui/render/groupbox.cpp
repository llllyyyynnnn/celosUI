#include "../ui.h"

namespace celosia::render::groupbox {
	void return_full(ImVec2* offset, ImVec2* offset_max, ImVec2* offset_size) {
		float spacing = animations::str_map["groupbox_active_spacing"];
		float size = ((ui::size.y - style::titlebar::height)) - style::frame::size_padding.y;

		*offset = {
			style::sidebar::width + style::frame::size_padding.x,
			style::titlebar::height + spacing + style::frame::size_padding.y
		};
		*offset_max = {
			ui::size.x - style::frame::size_padding.x,
			offset->y + size - style::frame::size_padding.y
		};

		*offset_size = {
			offset_max->x - offset->x,
			offset_max->y - offset->y
		};
	}
	void return_two(ImVec2* offset, ImVec2* offset_max, ImVec2* offset_size) {
		float spacing = animations::str_map["groupbox_active_spacing"];
		float size = ((ui::size.y - style::titlebar::height) / 2) - style::frame::size_padding.y;

		*offset = {
			style::sidebar::width + style::frame::size_padding.x,
			style::titlebar::height + spacing + style::frame::size_padding.y + (size * variables::config::ints["groupbox_index"])
		};
		*offset_max = {
			ui::size.x - style::frame::size_padding.x, 
			offset->y + size - style::frame::size_padding.y
		};

		*offset_size = {
			offset_max->x - offset->x, 
			offset_max->y - offset->y
		};
	}

	void body(ImDrawList* drawlist, const ImVec2 offset, const ImVec2 offset_max, const std::string title, const std::string description, e_group_layout layout) {
		ImColor a = style::general::main_color;
		ImColor b = style::themes::get_accent(a);

		drawlist->AddRectFilled(ImVec2(offset.x, offset.y + style::groupbox::height / 2), offset_max, style::themes::active.background_darker, style::general::rounding);

		switch (style::themes::active.tab_style) {
		case style::themes::e_tab_title_style::full:
			ImGui::AddRectFilledMultiColorRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), a, b, style::general::rounding); // ctodo: this function has weird artifacts (strange lines, possibly due to wrong sizes / might also just be an imgui issue)
			break;
		case style::themes::e_tab_title_style::minimal:
			ImGui::AddRectFilledHalfRounded(drawlist, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), style::themes::active.frame_fill, 4);
			drawlist->AddRectFilledMultiColor(ImVec2(offset.x, offset.y + (style::groupbox::height)-2), ImVec2(offset_max.x, offset.y + (style::groupbox::height)), a, b, b, a); // ctodo: make a func of this
			break;
		}

		render::text::font(drawlist, title.c_str(), ImVec2(offset.x + style::frame::size_padding.x, (offset.y + style::groupbox::height / 2) - (render::text::calc::font("a", resources::fonts::map["default"]).y / 2)), ImColor(255, 255, 255, 255), resources::fonts::map["default"]);
	}

	void begin(const std::string title, const std::string description, e_group_layout layout) {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		ImVec2 offset, offset_max, offset_size;
		return_two(&offset, &offset_max, &offset_size);

		body(drawlist_window, offset, offset_max, title, description, layout);
		ImGui::SetCursorPos(ImVec2(offset.x + style::frame::size_padding.x, offset.y + style::frame::size_padding.y + style::groupbox::height));
		ImGui::BeginChild(title.c_str(), ImVec2(offset_size.x - style::frame::size_padding.x, offset_size.y - style::groupbox::height - style::frame::size_padding.y));
	}

	void end() {
		variables::config::ints["groupbox_index"] += 1;
		ImGui::EndChild();
	}
}

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
