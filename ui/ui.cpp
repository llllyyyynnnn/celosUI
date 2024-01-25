#include "ui.h"
#include "Win32/ui_Win32.h"

float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

namespace celosia::ui { // ctodo: move this to render
    void main_window() {
        ImGui::Begin(variables::title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(celosia::ui::size);
        ImGui::SetWindowPos(ImVec2(0, 0));
        render::titlebar();
        render::sidebar();

        if (variables::temporary::strings["tab_current"] == "tab1") { // --> visible tab
            render::groupbox::begin("Groupbox A");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("group A " + std::to_string(i)).c_str());
            render::groupbox::end();

            render::groupbox::begin("Groupbox B");
            ImGui::ColorEdit3("Main Color", color); // ctodo: remake this
            style::general::main_color = { color[0], color[1], color[2], color[3] };
            render::groupbox::end();
        }
        else {
            render::groupbox::begin("Groupbox A", "test description AAA");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("group A " + std::to_string(i)).c_str());
            render::groupbox::end();
        }
        

        ImGui::End();
    }

    void render() {
        begin();

        render::drawlist_background = ImGui::GetBackgroundDrawList();
        render::drawlist_foreground = ImGui::GetForegroundDrawList();

        if (ui::active) {
            variables::config::ints["groupbox_index"] = 0;
            main_window();
        }

        /* use drawlists here */

        animations::functions::tab_switch();
        end();
    }
}