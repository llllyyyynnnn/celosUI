#include "../ui.h"

namespace celosia::render {
	void sidebar() {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		drawlist_window->AddRectFilled(ImVec2(0, style::titlebar::height), ImVec2(style::sidebar::width, ui::size.y), style::themes::active.background_darker, style::general::rounding_window);
		ImGui::SetCursorPos(ImVec2(style::general::padding.x, style::titlebar::height));
		ImGui::BeginChild("Sidebar", ImVec2(style::sidebar::width - style::general::padding.x, ui::size.y - style::titlebar::height));
		
		if (ImGui::Button("Tab One"))
			variables::temporary::strings["tab_active"] = "tab1";
		if (ImGui::Button("Tab Two"))
			variables::temporary::strings["tab_active"] = "tab2";


		ImGui::EndChild();
	}
} // ctodo: button layout