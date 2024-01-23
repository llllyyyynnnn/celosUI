#include "../Win32/ui_Win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace celosia_Win32::window {
    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DISPLAYCHANGE: // res changed
            //ui::variables::monitor::update();
            break;
        case WM_DEVICECHANGE: // monitor changed ?
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

    HWND create(LPCWSTR window_title, ImVec2 pos, ImVec2 size, long window_flags) {
        if (!(variables::windows.find(window_title) == variables::windows.end())) { // window already exists with same title / class
            DestroyWindow(variables::windows[window_title].second);
            UnregisterClassW(window_title, 0);
        }

        WNDCLASSEXW wc = {
            sizeof(wc),
            CS_HREDRAW | CS_VREDRAW,
            WndProc,
            0L, 0L,
            GetModuleHandle(nullptr),
            nullptr, nullptr, nullptr, nullptr,
            window_title,
            nullptr
        };

        RegisterClassExW(&wc);

        const HWND hwnd = CreateWindowExW(
            window_flags /*| WS_EX_TRANSPARENT*/,
            wc.lpszClassName,
            window_title,
            WS_POPUP, // WS_OVERLAPPED
            pos.x, pos.y, size.x, size.y,
            nullptr, nullptr,
            wc.hInstance,
            nullptr
        );

        variables::windows[window_title] = { wc, hwnd };
        return hwnd;
    }

    void show(HWND hwnd) {
        ShowWindow(hwnd, SW_SHOWDEFAULT);
        UpdateWindow(hwnd);
    }
    
    void hide(HWND hwnd) {
        ShowWindow(hwnd, SW_HIDE);
        UpdateWindow(hwnd); // unsure if this is needed here
    }

    void move(HWND hwnd, ImVec2 pos) { // ctodo: get old size and use it
        SetWindowPos(hwnd, 0, pos.x, pos.y, celosia::ui::size.x, celosia::ui::size.y, 0);
    }

    void resize(HWND hwnd, ImVec2 size) { // ctodo: get old pos and use it
        SetWindowPos(hwnd, 0, 0, 0, size.x, size.y, 0);
    }

    void destroy() { // ctodo: fix (this wont be necessary, there's only 1 window support)
        // loop throuhg all windows, remove wc, delete d3d device

        for (auto const& [key, val] : variables::windows)
        {
            std::string converted = celosia::functions::ConvertLPCWSTRToString(key);
            std::cout << converted << std::endl;
        }
    }
}