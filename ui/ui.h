// CTODO: check this out & changes here take a while to compile as a result of it being included everywhere

#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <d3d11.h>
#include <tchar.h>
#include <dwmapi.h>

#include <iostream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <map>

#include "../external/imgui/imgui.h"
#include "../external/imgui/imgui_internal.h"
#include "../external/imgui/dx11/imgui_impl_dx11.h"
#include "../external/imgui/win32/imgui_impl_win32.h"

#include "resources/resources.h"
#include "style/style.h"
#include "render/render.h"
#include "debug/debug.h"
#include "wrappers/wrappers.h"

#pragma comment(lib, "d3d11.lib")

namespace celosia {
	namespace initialize {
		void context(HWND hwnd = nullptr);
		void fonts();
	}

	namespace resources {
		namespace fonts {
			bool add(std::string resourcename, std::string fontname, int fontsize);
			inline std::unordered_map<std::string, ImFont*> map;
		}
	}

	namespace D3D {
		inline ID3D11Device* device;
		inline ID3D11DeviceContext* device_context;
		inline IDXGISwapChain* swapchain;
		inline ID3D11RenderTargetView* render_target_view;
	}

	namespace variables {
		inline static const char* title = "celos";
		inline static const char* version = "UI"; // ctodo: turn into a struct / class
		
		namespace config {
			inline std::unordered_map<std::string, int> ints;
			inline std::unordered_map<std::string, float> floats;
			inline std::unordered_map<std::string, bool> bools;
			inline std::unordered_map<std::string, ImVec2> vec2;
			inline std::unordered_map<std::string, std::string> strings;
		}

		namespace temporary {
			inline std::unordered_map<std::string, int> ints;
			inline std::unordered_map<std::string, float> floats;
			inline std::unordered_map<std::string, bool> bools;
			inline std::unordered_map<std::string, ImVec2> vec2;
			inline std::unordered_map<std::string, std::string> strings;
		}
	}

	namespace monitor {
		inline ImVec2 size;

		void update();
	}

	namespace animations {
		inline std::unordered_map<std::string, float> str_map;
		inline std::unordered_map<int, float> int_map;
		inline float base_speed = 2.f;

		enum e_method{ smooth, linear };

		namespace functions {
			float calc_linear(float current_value, const float goal_value, float speed);
			float calc_smooth(float current_value, const float goal_value, float speed);

			float linear(const std::string& value, const float goal_value, float speed);
			float smooth(const std::string& value, const float goal_value, float speed);

			float linear(const int& value, const float goal_value, float speed);
			float smooth(const int& value, const float goal_value, float speed);

			void tab_switch();
		}

		float set(const std::string& value, const float goal_value, float speed = 0, e_method method = e_method::smooth);
		ImVec2 set(const std::string& value, const ImVec2 goal_value, float speed = 0, e_method method = e_method::smooth);
		ImVec4 set(const std::string& value, const ImVec4 goal_value, float speed = 0, e_method method = e_method::smooth);

		float set(const int& value, const float goal_value, float speed = 0, e_method method = e_method::smooth);
		ImVec2 set(const int& value, const ImVec2 goal_value, float speed = 0, e_method method = e_method::smooth);
		ImVec4 set(const int& value, const ImVec4 goal_value, float speed = 0, e_method method = e_method::smooth);
	}

	namespace ui {
		inline ImVec2 size = { 800, 600 };
		inline bool active = true;

		void begin();
		void end();
		void render();
	}

	namespace functions {
		std::string ConvertLPCWSTRToString(LPCWSTR lpcwszStr);

		ImVec2 mouse_vec2();
		bool hovered(const ImVec2& pos1, const ImVec2& pos2);
		
		void spacing(int amount);

		int clamp(int val, const int& min, const int& max);
		float clamp(float val, const float& min, const float& max);
		void clamp(int* val, const int& min, const int& max);
		void clamp(float* val, const float& min, const float& max);
	}

	namespace inputsystem {
		namespace registry {
			inline std::unordered_map<DWORD, bool> down; // should probably clear these occasionally
			inline std::unordered_map<DWORD, bool> up;
			inline std::unordered_map<DWORD, bool> watched; // keys that are actively being refreshed globally
		}

		namespace key {
			bool down(const DWORD& key);
			bool up(const DWORD& key);
			bool held(const DWORD& key);

			void watch(const DWORD& key);   // will add to an array that is constantly being checked, unlike others that depend on functions to watch for them
											// this is only efficient if you are trying to monitor the same key in multiple places and don't want to call getasynckeystate each time, or just for easier management of it
											// it is also important to use for first calls on key::down as there's an issue where it detects a key being held down as just being pressed, which it wasn't
											// this is due to the lack of data from not being watched
			void unwatch(const DWORD& key);
		}

		void refresh();		// any references such as watched[KEY] will end up creating the key
							// unintended, CTODO: fix
							// or use watched.find / watched.at as these won't create a reference
							// this has to be ran every frame
	}
}