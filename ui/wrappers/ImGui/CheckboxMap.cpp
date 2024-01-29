#include "../../ui.h"


namespace ImGui {
    bool CheckboxMap(const char* label) { return Checkbox(label, &celosia::variables::config::bools[label]); }
}