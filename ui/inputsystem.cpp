/* CTODO: Use ImGui inputsystem, as those are supported across multiple platforms that do not have GetASyncKeyState */

#include "ui.h"

namespace celosia::inputsystem {
	bool key::down(const DWORD& key) {
		if (!(registry::watched.find(key) == registry::watched.end())) { // this really does not seem efficient at all i'm gonna be completely honest CTODO: Rewrite, inefficient
			if (registry::watched[key] && !registry::down[key]) {
				registry::down[key] = true;
				return true;
			}
			else {
				if (!registry::watched[key] && registry::down[key])
					registry::down[key] = false;
				return false;
			}
		}
		else {
			if (GetAsyncKeyState(key) && !registry::down[key]) { // key has just went down
				registry::down[key] = true;
				return true;
			}
			else {
				if (!GetAsyncKeyState(key) && registry::down[key]) // reset
					registry::down[key] = false;
				return false;
			}
		}
	}

	bool key::up(const DWORD& key) {
		if (!(registry::watched.find(key) == registry::watched.end())) {
			if (registry::watched[key] && !registry::up[key]) {
				registry::up[key] = true;
				return false;
			}
			else {
				if (!registry::watched[key] && registry::up[key])
					registry::up[key] = false;
				return true;
			}
		}
		else {
			if (GetAsyncKeyState(key) && !registry::up[key]) {
				registry::up[key] = true;
				return false;
			}
			else {
				if (!GetAsyncKeyState(key) && registry::up[key]) {
					registry::up[key] = false;
					return true;
				}
				return false;
			}
		}
	}

	bool key::held(const DWORD& key) { // key is currently down
		return GetAsyncKeyState(key) & 0x8000;
	}

	void key::watch(const DWORD& key) { // add key to the watchlist
		registry::watched.insert({ key, false });
	}

	void key::unwatch(const DWORD& key) { // remove key from the watchlist
		registry::watched.erase(key);
	}

	void refresh() { // loop through all of the keys in watchlist and validate them (this does not seem all that efficient either)
		for (auto const& [key, val] : registry::watched)
			registry::watched[key] = key::held(key);
	}
}