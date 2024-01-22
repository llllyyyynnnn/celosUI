#include "../ui.h"

namespace celosia::render {
	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding) { // improper way of doing it but works for now, rework later when i got time
		drawlist->AddRectFilled(ImVec2(min.x, min.y), ImVec2(min.x + 100, max.y), one, rounding); // ctodo: add this in imgui.cpp & .h as RectFilledMultiColorRounded
		drawlist->AddRectFilled(ImVec2(max.x - 100, min.y), ImVec2(max.x, max.y), two, rounding); // edges

		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding, min.y), ImVec2(max.x - rounding, min.y + rounding / 2), one, two, two, one);
		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding, max.y), ImVec2(max.x - rounding, max.y - rounding / 2), one, two, two, one);
		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding / 2, min.y + rounding / 2), ImVec2(max.x - rounding / 2, max.y - rounding / 2), one, two, two, one); // fill
	}
}