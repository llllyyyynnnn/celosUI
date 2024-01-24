#include "../ui.h"

namespace celosia::style::themes {
	ImColor get_accent(ImColor clr) {  // CTODO: improper, works for now
		return ImColor{ clr.Value.x, clr.Value.y * 0.69f, clr.Value.z * 1.5f, clr.Value.w }; 
	}
}