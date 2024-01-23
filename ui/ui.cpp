#include "ui.h"
#include "Win32/ui_Win32.h"


namespace celosia::ui { // ctodo: github
    void main_window() {
        ImGui::Begin(variables::title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(celosia::ui::size);
        ImGui::SetWindowPos(ImVec2(0, 0));
        render::titlebar();
        render::sidebar();

        render::groupbox::begin("test");
        render::groupbox::end();
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
        ImGui::TabButton();

        end();
    }
}