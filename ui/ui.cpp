#include "ui.h"
#include "Win32/ui_Win32.h"

float color[4] = { celosia::style::general::main_color.Value.x, celosia::style::general::main_color.Value.y, celosia::style::general::main_color.Value.z, celosia::style::general::main_color.Value.w};

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
                if (ImGui::Button(("group A " + std::to_string(i)).c_str()))
                    debug::log("Button " + std::to_string(i) + " has been hit");
            render::groupbox::end();

            render::groupbox::begin("Groupbox B", "Checkboxes");
            for (int i = 0; i < 20; i++)
                ImGui::CheckboxMap(("Checkbox " + std::to_string(i)).c_str());
            render::groupbox::end();
        }
        else {
            render::groupbox::begin("Groupbox B");
            const char* test[] = {"Item A", "Item B", "Item C"};
            ImGui::Combo("test", &variables::config::ints["test_combo"], test, 3, 3);

            ImGui::ColorEdit4("Main Color", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoSidePreview /*| ImGuiColorEditFlags_AlphaBar*/); // ctodo: remake this
            style::general::main_color = { color[0], color[1], color[2], color[3] };

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