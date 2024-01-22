#pragma once

namespace ImGui { // add extra ImGui components here, in order to keep it all in one place
	bool TabButton();
	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding);
	void AddRectFilledHalfRounded(ImDrawList* drawlist, const ImVec2& min, const ImVec2& max, const ImColor& clr, const int& rounding);
}