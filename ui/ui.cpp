#include "ui.h"
#include "Win32/ui_Win32.h"


namespace celosia::ui { // ctodo: github
	void initialize(HWND hwnd) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        render::io = &ImGui::GetIO();

        if (hwnd != nullptr)
            ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(D3D::device, D3D::device_context);

        style::themes::initialize();
        style::themes::set(style::themes::dark);
	}

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
    void main_window() {
        ImGui::Begin(variables::title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(celosia::ui::size);
        ImGui::SetWindowPos(ImVec2(0, 0));
        render::titlebar();
        render::sidebar();

        render::groupbox_begin("test");
        render::groupbox_end();
        ImGui::End();
    }

    void render() {
        begin();

        render::drawlist_background = ImGui::GetBackgroundDrawList();
        render::drawlist_foreground = ImGui::GetForegroundDrawList();

        if (ui::active) {
            main_window();
        }

        /* use drawlists here */

        animations::functions::tab_switch();

        end();
    }
}