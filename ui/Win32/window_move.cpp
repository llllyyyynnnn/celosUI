#include "../Win32/ui_Win32.h"

bool dragging = false;
bool ignore_click = false;

ImVec2 offset;

void celosia_Win32::window::drag() { // ctodo: make sure these aren't being handled when there's no ui visible, preferably in loop
    RECT window_pos;
    HWND hwnd = variables::windows[celosia_Win32::variables::main_window_title].second;
    GetWindowRect(hwnd, &window_pos);

    ImVec2 mouse_pos = celosia::functions::mouse_vec2();


    if (dragging) {
        dragging = GetAsyncKeyState(VK_LBUTTON);
        move(hwnd, ImVec2(mouse_pos.x - offset.x, mouse_pos.y - offset.y));
        return;
    }

    if (ignore_click)
        ignore_click = GetAsyncKeyState(VK_LBUTTON); // ctodo: use actual input sys
    
    if ((mouse_pos.x >= window_pos.left && mouse_pos.x <= window_pos.right) &&
        (mouse_pos.y >= window_pos.top && mouse_pos.y <= window_pos.top + celosia::style::titlebar::height)) {
        if (GetAsyncKeyState(VK_LBUTTON) && !ignore_click) { // ctodo: only on keydown, the other one can remain async
            dragging = true;
            offset = { mouse_pos.x - window_pos.left, mouse_pos.y - window_pos.top };
        }
    }
    else {
        if (GetAsyncKeyState(VK_LBUTTON))
            ignore_click = true;

    }
}