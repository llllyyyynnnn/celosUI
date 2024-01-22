#include "../Win32/ui_Win32.h"

namespace celosia_Win32::window {
    void enable_transparency(HWND hwnd) { // 0, 0, 0, 0 will turn invisible
        SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
        {
            RECT clarea{}; GetClientRect(hwnd, &clarea);
            RECT warea{}; GetWindowRect(hwnd, &warea);

            POINT difference{};
            ClientToScreen(hwnd, &difference);

            const MARGINS margin{
                warea.left + difference.x - warea.left,
                warea.top + difference.y - warea.top,
                clarea.right, clarea.bottom
            };

            DwmExtendFrameIntoClientArea(hwnd, &margin);
        }
    }

    void enable_blur(HWND hwnd, int accent) {
        struct ACCENTPOLICY {
            int na;
            int nf;
            int nc;
            int nA;
        };
        struct WINCOMPATTRDATA {
            int na;
            PVOID pd;
            ULONG ul;
        };

        const HINSTANCE hm = LoadLibrary(L"user32.dll");
        if (hm) {
            typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

            const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
            if (SetWindowCompositionAttribute) {
                ACCENTPOLICY policy = { accent, 0, 0, 0 };
                WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
                SetWindowCompositionAttribute(hwnd, &data);
            }
            FreeLibrary(hm);
        }
    }

}