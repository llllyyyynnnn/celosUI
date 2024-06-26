#include "../ui.h"

namespace celosia::render {
	void titlebar() {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		drawlist_window->AddRectFilled(ImVec2(0, 0), ImVec2(ui::size.x, style::titlebar::height), style::themes::active.background_darker, style::general::rounding_window);
		
		ImGui::PushFont(resources::fonts::map["title"]);

		ImVec2 title_size = ImGui::CalcTextSize(variables::title);
		float y_center = (style::titlebar::height - title_size.y) / 2;

		drawlist_window->AddText(
			ImVec2(style::frame::size_padding.x, y_center),
			style::themes::active.text,
			variables::title
		);

		drawlist_window->AddText(
			ImVec2(style::frame::size_padding.x + title_size.x, y_center),
			style::general::main_color,
			variables::version
		);

		ImGui::PopFont();
	}
}