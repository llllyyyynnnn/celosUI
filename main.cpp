#include <iostream>

#include "ui/Win32/ui_Win32.h"

int main(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    HWND ui = celosia_Win32::window::create(celosia_Win32::variables::main_window_title, ImVec2(0, 0), celosia::ui::size, WS_EX_TOPMOST | WS_EX_LAYERED);

    celosia_Win32::D3D::CreateDevice(ui);
    celosia::initialize::context(ui);
	celosia::initialize::fonts();

    celosia_Win32::window::enable_transparency(ui);
    celosia_Win32::window::enable_blur(ui, 4);
    celosia_Win32::window::show(ui);

    bool running = false;
    while (!running)
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = true;
        }

        if (running)
            break;

        celosia::ui::render();
        if(celosia::ui::active)
            celosia_Win32::window::drag();

        BringWindowToTop(ui); // only do this for crosshair overlay
    }

    // unload everything
    celosia_Win32::window::destroy();
	return 0;
}