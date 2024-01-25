#include "ui.h"
#include "Win32/ui_Win32.h"


namespace celosia::ui { // ctodo: move this to render
    void main_window() {
        ImGui::Begin(variables::title, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(celosia::ui::size);
        ImGui::SetWindowPos(ImVec2(0, 0));
        render::titlebar();
        render::sidebar();

        // -> visible tab

        if (variables::temporary::strings["tab_current"] == "tab1") {
            render::groupbox::begin("Groupbox A");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("group A " + std::to_string(i)).c_str());
            render::groupbox::end();

            render::groupbox::begin("Groupbox B");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("group B " + std::to_string(i)).c_str());
            render::groupbox::end();
        }
        
        if (variables::temporary::strings["tab_current"] == "tab2") {
            render::groupbox::begin("You've entered tab2");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("Tab 2 " + std::to_string(i)).c_str());
            render::groupbox::end();

            render::groupbox::begin("Groupbox D");
            for (int i = 0; i < 20; i++)
                ImGui::Button(("group D " + std::to_string(i)).c_str());
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