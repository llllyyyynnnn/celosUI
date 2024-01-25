#include "../ui.h"

namespace celosia::style::themes {
	ImVec4 rgb_vec4(const float& r, const float& g, const float& b, const float& a) { return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f); }
	ImVec4 rgb_vec4(const ImColor& rgba) { return ImVec4(rgba.Value.x, rgba.Value.y, rgba.Value.z, rgba.Value.w); }

	ImColor rgb_accent(ImColor clr) {  // CTODO: improper, works for now
		return ImColor{ clr.Value.x, clr.Value.y * 0.69f, clr.Value.z * 1.5f, clr.Value.w };
	}

	ImColor rgb_intensity(ImColor clr, float percentage) {
		return ImColor(clr.Value.x * percentage, clr.Value.y * percentage, clr.Value.z * percentage, clr.Value.w);
	}
}