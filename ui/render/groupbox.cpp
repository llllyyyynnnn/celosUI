#include "../ui.h"



void celosia::render::begingroupbox(std::string title, std::string description) {
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

	drawlist_window->AddRectFilled(ImVec2(offset.x, offset.y + (style::groupbox::height / 2)), offset_max, style::themes::active.background_darker, style::general::rounding);
	render::AddRectFilledMultiColorRounded(drawlist_window, offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), ImColor(255,255,255,255), ImColor(100, 255, 255, 255), 8);

	ImGui::SetCursorPos(ImVec2(offset.x + style::groupbox::padding, offset.y + style::groupbox::height + style::groupbox::padding));
	ImGui::BeginChild(title.c_str(), ImVec2(offset_available.x - style::groupbox::padding, offset_available.y - style::groupbox::height - style::groupbox::padding));
}

void celosia::render::endgroupbox() {
	ImGui::EndChild();
}