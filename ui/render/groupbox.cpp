#include "../ui.h"



void celosia::render::groupbox(std::string title, std::string description) {
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

	drawlist_window->AddRectFilled(offset, ImVec2(offset_max.x, offset.y + style::groupbox::height), ImColor(255, 255, 255, 255), style::general::rounding);
	drawlist_window->AddRectFilled(ImVec2(offset.x, offset.y + style::groupbox::height), offset_max, ImColor(0, 0, 0, 255), style::general::rounding);

	ImGui::SetCursorPos(ImVec2(offset.x + style::groupbox::padding, offset.y + style::groupbox::height + style::groupbox::padding));
	ImGui::BeginChild(title.c_str(), ImVec2(offset_available.x - style::groupbox::padding, offset_available.y - style::groupbox::height - style::groupbox::padding));
	for (int i = 0; i < 50; i++)
		ImGui::Button(("ape ape ape " + std::to_string(i + 1)).c_str());

	ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
	ImGui::EndChild();
}