#include "../../ui.h"

namespace ImGui {
	void AddRectFilledMultiColorRounded(ImDrawList* drawlist, const ImVec2 min, const ImVec2 max, const ImColor one, const ImColor two, const int& rounding) { // improper way of doing it but works for now, rework later when i got time
		float size = celosia::functions::clamp((max.x - min.x) / 2.f, 0.f, 25.f);

		drawlist->AddRectFilled(ImVec2(min.x, min.y), ImVec2(min.x + size, max.y), one, rounding);
		drawlist->AddRectFilled(ImVec2(max.x - size, min.y), ImVec2(max.x, max.y), two, rounding); // edges

		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding, min.y), ImVec2(max.x - rounding, min.y + rounding / 2), one, two, two, one);
		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding, max.y), ImVec2(max.x - rounding, max.y - rounding / 2), one, two, two, one);
		drawlist->AddRectFilledMultiColor(ImVec2(min.x + rounding / 2, min.y + rounding / 2), ImVec2(max.x - rounding / 2, max.y - rounding / 2), one, two, two, one); // fill
	}
}
