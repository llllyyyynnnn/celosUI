#include "../ui.h"

namespace celosia::style {
	namespace themes {
		void init_dark() {
			dark.text = ImColor(255, 255, 255, 255);
			dark.background = ImColor(12, 12, 12, 180);
			dark.background_darker = ImColor(10, 10, 10, 200);
			dark.idle = ImColor(18, 18, 18, 255);
			dark.hovered = ImColor(64, 64, 64, 255);
			dark.held = ImColor(16, 16, 16, 255);
			dark.frame_border = ImColor(0, 0, 0, 0);
			dark.frame_fill = ImColor(16, 16, 16, 255);
			dark.tab_style = e_tab_title_style::full;
		}

		void init_light() {
			light.text = ImColor(12, 12, 12, 255);
			light.background = ImColor(255, 255, 255, 255);
			light.background_darker = ImColor(200, 200, 200, 255);
			light.idle = ImColor(0, 0, 0, 255);
			light.tab_style = e_tab_title_style::full;
		}

		void initialize(){
			init_dark();
			init_light();
		}

		void set(t_theme theme) {
			active = theme; // ctodo: lerp
			style::push();
		}
	}

	void push() { // ctodo: fix this, broken & doesn't work (no popstylevar / popstylecolor, will crash if ran more than once)
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, general::rounding);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, frame::size_padding);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, general::rounding_window);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // idk if this should be customizable it's annoying
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 4);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, general::spacing);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, style::themes::rgb_vec4(themes::active.background));

		ImGui::PushStyleColor(ImGuiCol_FrameBg, style::themes::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, style::themes::rgb_vec4(themes::active.hovered));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, style::themes::rgb_vec4(themes::active.held));

		ImGui::PushStyleColor(ImGuiCol_CheckMark, style::themes::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, style::themes::rgb_vec4(themes::active.background_darker));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, style::themes::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_Border, style::themes::rgb_vec4(themes::active.frame_border));

		ImGui::PushStyleColor(ImGuiCol_TitleBg, style::themes::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, style::themes::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, style::themes::rgb_vec4(themes::active.idle));
	}
}