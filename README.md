ctodo = todo

InputSystem
Freetype
Image Loading
Button Layout (Tabs)
Theme Lerp & PushStyleColor / Var
Color Picker
Scrollbar.h

res does not have to be 1920x1080

redo font spacing code
redo gradient code
redo imgui::endchild pushclip, combo pushclip, begin pushbclip
RenderFrameFunctions

for animations using renderframeanimations, add an index that is reset on every frame to avoid mixing up

b4->
switch layout, font, color, gradient, sizes



		float size = ((ui::size.y - style::titlebar::height) / 2) - style::frame::size_padding.y;

		*offset = {
			style::sidebar::width + animations::str_map["groupbox_active_spacing"] + style::frame::size_padding.x,
			style::titlebar::height + animations::str_map["groupbox_active_spacing"] + style::frame::size_padding.y + (size * variables::config::ints["groupbox_index"])
		};
		*offset_max = {
			ui::size.x - style::frame::size_padding.x - animations::str_map["groupbox_active_spacing"],
			offset->y + size - style::frame::size_padding.y - animations::str_map["groupbox_active_spacing"]
		};

		*offset_size = {
			offset_max->x - offset->x, 
			offset_max->y - offset->y
		};