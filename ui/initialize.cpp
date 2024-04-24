#include "ui.h"

namespace celosia::resources { //ctodo: move to resources/ & make a fontstruct
    bool fonts::add(std::string resourcename, std::string fontname, int fontsize) {
        std::string fontpath = fontname; // "H:\\SRC\\fonts\\" + fontname;
        fonts::map[resourcename] = render::io->Fonts->AddFontFromFileTTF(fontpath.c_str(), fontsize);

        return true;
    }
}

namespace celosia::initialize {
    void context(HWND hwnd) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        render::io = &ImGui::GetIO();

        if (hwnd != nullptr)
            ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(D3D::device, D3D::device_context);

        style::themes::initialize();
        style::themes::set(style::themes::dark);
    }

    void fonts() { // ctodo: add bytes into a .h file so there's no need for external files
        resources::fonts::add("default", "Poppins-Regular.ttf", 16);
        resources::fonts::add("default_smaller", "Poppins-Regular.ttf", 14);

        resources::fonts::add("title", "Poppins-Bold.ttf", 24);
    } 

    // ctodo: freetype
    // ctodo: image loading (dx11)
}

namespace celosia::ui {
    void begin() {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    void end() {
        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0,0,0,0 };
        D3D::device_context->OMSetRenderTargets(1, &D3D::render_target_view, nullptr);
        D3D::device_context->ClearRenderTargetView(D3D::render_target_view, clear_color_with_alpha);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        D3D::swapchain->Present(1, 0); // Present with vsync, (use 0, 0 for no vsync, although unnecessary because I don't think I'll be needing 1000+ fps for this. Maybe limit it to 60 fps or something even.)
    }
}