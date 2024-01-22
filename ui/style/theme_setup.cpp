#include "../ui.h"

namespace celosia::style {
	namespace themes {
		void init_dark() {
			dark.background = ImColor(12, 12, 12, 180);
			dark.background_darker = ImColor(10, 10, 10, 200);
			dark.idle = ImColor(16, 16, 16, 255);
			dark.hovered = ImColor(64, 64, 64, 255);
			dark.held = ImColor(32, 32, 32, 255);
			dark.frame_border = ImColor(0, 0, 0, 0);
		}

		void init_light() {
			light.background = ImColor(255, 255, 255, 255);
			light.background_darker = ImColor(200, 200, 200, 255);
			light.idle = ImColor(0, 0, 0, 255);
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

	void push() {
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, general::rounding);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, frame::size_padding);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, general::rounding_window);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // idk if this should be customizable it's annoying
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 4);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, general::spacing);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, functions::rgb_vec4(themes::active.background));

		ImGui::PushStyleColor(ImGuiCol_FrameBg, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, functions::rgb_vec4(themes::active.hovered));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, functions::rgb_vec4(themes::active.held));
/*
		ImGui::PushStyleColor(ImGuiCol_Button, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, functions::rgb_vec4(themes::active.idle));
*/
		ImGui::PushStyleColor(ImGuiCol_CheckMark, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, functions::rgb_vec4(themes::active.background_darker));
		ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_Border, functions::rgb_vec4(themes::active.frame_border));

		ImGui::PushStyleColor(ImGuiCol_TitleBg, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, functions::rgb_vec4(themes::active.idle));
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, functions::rgb_vec4(themes::active.idle));
	}
}