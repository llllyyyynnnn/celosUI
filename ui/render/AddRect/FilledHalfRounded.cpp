#include "../../ui.h"

namespace celosia::render {
	void AddRectFilledHalfRounded(ImDrawList* drawlist, const ImVec2& min, const ImVec2& max, const ImColor& clr, const int& rounding) {
		drawlist->AddRectFilled(min, max, clr, rounding);
		drawlist->AddRectFilled(ImVec2(min.x, min.y + (max.y - min.y) / 2), max, clr, 0);
	}
}