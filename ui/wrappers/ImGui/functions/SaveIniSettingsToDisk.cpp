#include "../../../ui.h"

void ImGui::SaveIniSettingsToDisk(const char* ini_filename)
{
    /* extremely annoying, saves unnecessary files that won't ever be used and in the case they are reused they often break more than help
    ImGuiContext& g = *GImGui;
    g.SettingsDirtyTimer = 0.0f;
    if (!ini_filename)
        return;

    size_t ini_data_size = 0;
    const char* ini_data = SaveIniSettingsToMemory(&ini_data_size);
    ImFileHandle f = ImFileOpen(ini_filename, "wt");
    if (!f)
        return;
    ImFileWrite(ini_data, sizeof(char), ini_data_size, f);
    ImFileClose(f);

    std::cout << "save requested" << std::endl;
    */
}