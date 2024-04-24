#pragma once

namespace celosia::style {
	namespace general {
		inline ImColor main_color = { 189, 122, 255,255 };
		inline static int rounding = 4;
		inline static int rounding_window = 0;
		inline static int scroll_speed = 15.f;
		inline static int scroll_multiplier = 4;
		inline static ImVec2 padding = {10, 10};
		inline static ImVec2 spacing = {0, 4};
	}
	namespace titlebar {
		inline static float height = 45;
		inline static int padding = 2;
	}
	namespace sidebar {
		inline static float width = 165;
	}
	namespace frame {
		inline static ImVec2 size_padding = {10,10};
		inline static int border_size = 2;
		inline static int border_size_animated = 2;

		inline static float tab_switch_animation_max = 16;
		inline static int tab_switch_animation_speed = 2;
	}
	namespace groupbox {
		inline static float height = 40;
		inline static int padding = titlebar::padding * 4;
	}
/*
	namespace checkbox {
		inline static int size = 10;
	}
*/

	namespace themes {
		enum e_tab_title_style { full, minimal };

		struct t_theme {
			std::string name;
			e_tab_title_style tab_style;

			ImColor background;
			ImColor background_darker;

			ImColor frame_border;
			ImColor frame_fill;

			ImColor idle;
			ImColor held;
			ImColor hovered;
			ImColor active;

			ImColor text;
		};

		inline t_theme dark;
		inline t_theme light;

		inline t_theme active;

		void initialize();
		void set(t_theme theme);

		ImVec4 rgb_vec4(const float& r, const float& g, const float& b, const float& a);
		ImVec4 rgb_vec4(const ImColor& rgba);

		ImColor rgb_accent(ImColor clr);
		ImColor rgb_intensity(ImColor clr, float percentage);
	}

	void push();
}