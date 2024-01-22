#include "../ui.h"

namespace celosia::render {
	void titlebar() {
		ImDrawList* drawlist_window = ImGui::GetWindowDrawList();
		drawlist_window->AddRectFilled(ImVec2(0, 0), ImVec2(ui::size.x, style::titlebar::height), style::themes::active.background_darker, style::general::rounding_window);
	}
}