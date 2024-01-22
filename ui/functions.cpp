#include "ui.h"

namespace celosia::monitor {
	void update(){
		size.x = GetSystemMetrics(SM_CXSCREEN);
		size.y = GetSystemMetrics(SM_CYSCREEN);
	}
}

namespace celosia::functions {
	std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr)
	{
		int strLength = WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, nullptr, 0, nullptr, nullptr);
		std::string str(strLength, 0);
		WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0], strLength, nullptr, nullptr);
		return str;
	} // https://www.geeksforgeeks.org/convert-lpcwstr-to-std_string-in-cpp/

	ImVec4 rgb_vec4(const float& r, const float& g, const float& b, const float& a) { return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f); }
	ImVec4 rgb_vec4(const ImColor& rgba) { return ImVec4(rgba.Value.x, rgba.Value.y, rgba.Value.z, rgba.Value.w); }
	ImVec2 mouse_vec2() {
		POINT p;
		if (GetCursorPos(&p))
			return ImVec2(p.x, p.y);
		else
			return ImVec2(0, 0);
	};

	bool hovered(const ImVec2& pos1, const ImVec2& pos2) {
		ImVec2 mouse_pos = ImGui::GetMousePos();
		return ((mouse_pos.x >= pos1.x && mouse_pos.x <= pos2.x) && (mouse_pos.y >= pos1.y && mouse_pos.y <= pos2.y));
	}

	void update_hotkeys() {
		//ctodo: remake
	}

	void spacing(int amount) {
		for (int i = 0; i < amount; i++)
			ImGui::Spacing();
	}

	int clamp(int val, const int& min, const int& max) {
		if (val > max) val = max;
		if (val < min) val = min;
		return val;
	}
	float clamp(float val, const float& min, const float& max) {
		if (val > max) val = max;
		if (val < min) val = min;
		return val;
	}
	void clamp(int* val, const int& min, const int& max) {
		if (*val > max) *val = max;
		if (*val < min) *val = min;
	}
	void clamp(float* val, const float& min, const float& max) {
		if (*val > max) *val = max;
		if (*val < min) *val = min;
	}
}