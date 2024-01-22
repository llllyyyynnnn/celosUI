#include "debug.h"

namespace celosia::debug {
	void log(std::string str) {
	#ifdef _DEBUG
		std::cout << "\033[1;35m" << "[DEBUG] " << "\033[0m" << str << "\n";
	#endif
	}
}