#include "../ui.h"

namespace celosia::render::text {
	namespace calc {
		ImVec2 font(const char* text, ImFont* font) { // there has to be better methods of doing this but it'll do for now
			ImGui::PushFont(font);
			ImVec2 size = ImGui::CalcTextSize(text);
			ImGui::PopFont();

			return size;
		}
	}
	void font(ImDrawList* drawlist, const char* text, ImVec2 pos, ImColor clr, ImFont* font) { // usage: single use text calls that require a different font, to avoid making the code a mess
		ImGui::PushFont(font);
		drawlist->AddText(pos, clr, text);
		ImGui::PopFont();
	}
} 