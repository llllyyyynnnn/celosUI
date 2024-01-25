#include "../ui.h"

namespace celosia::animations::functions {
	void tab_switch() {
		if (variables::temporary::strings["tab_old"] != variables::temporary::strings["tab_active"]) {
			variables::temporary::bools["tab_switch_animation_active"] = true;
			variables::temporary::bools["tab_switch_animation_down"] = true;

			variables::temporary::strings["tab_old"] = variables::temporary::strings["tab_active"];

			debug::log("tab switch animation activated");
		}

		if (variables::temporary::bools["tab_switch_animation_active"]) {
			if (variables::temporary::bools["tab_switch_animation_down"] == true)
				animations::set("groupbox_active_spacing", style::frame::tab_switch_animation_max * 2, style::frame::tab_switch_animation_speed, animations::e_method::smooth);
			else
				animations::set("groupbox_active_spacing", 0, style::frame::tab_switch_animation_speed, animations::e_method::smooth);

			if (animations::str_map["groupbox_active_spacing"] >= style::frame::tab_switch_animation_max)
				variables::temporary::bools["tab_switch_animation_down"] = false;

			if (variables::temporary::bools["tab_switch_animation_down"] && animations::str_map["groupbox_active_spacing"] == 0) 
				variables::temporary::bools["tab_switch_animation_active"] = false;

			float overlay_alpha = animations::str_map["groupbox_active_spacing"] / style::frame::tab_switch_animation_max;
			ImColor overlay_color = style::themes::active.background;
			overlay_color.Value.w = overlay_alpha;

			render::drawlist_foreground->AddRectFilled(
				ImVec2(style::sidebar::width, style::titlebar::height),
				ImVec2(style::sidebar::width + ui::size.x - style::frame::size_padding.x, style::titlebar::height + ui::size.y - style::frame::size_padding.y),
				overlay_color
			);

			if (!variables::temporary::bools["tab_switch_animation_down"])
				variables::temporary::strings["tab_current"] = variables::temporary::strings["tab_active"]; // allow the new groupbox to become visible
		}
	}
}