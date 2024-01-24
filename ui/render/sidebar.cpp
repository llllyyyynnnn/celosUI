#include "../ui.h"

namespace celosia::render {
	void sidebar() {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		drawlist_window->AddRectFilled(ImVec2(0, style::titlebar::height), ImVec2(style::sidebar::width, ui::size.y), style::themes::active.background_darker, style::general::rounding_window);
		ImGui::SetCursorPos(ImVec2(style::general::padding.x, style::titlebar::height));
		ImGui::BeginChild("Sidebar", ImVec2(style::sidebar::width - style::general::padding.x, ui::size.y - style::titlebar::height));
		
		if (ImGui::TabButton("Tab One"))
			variables::temporary::strings["tab_active"] = "tab1";
		if (ImGui::TabButton("Tab Two"))
			variables::temporary::strings["tab_active"] = "tab2";
		if (ImGui::Button("switch layout")) {

			if (style::themes::active.tab_style == style::themes::e_tab_title_style::full)
				style::themes::active.tab_style = style::themes::e_tab_title_style::minimal;
			else
				style::themes::active.tab_style = style::themes::e_tab_title_style::full;

		}

		ImGui::EndChild();
	}
} // ctodo: button layout