#include <iostream>

#include "ui/Win32/ui_Win32.h"

int main(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    HWND ui = celosia_Win32::window::create(celosia_Win32::variables::main_window_title, ImVec2(0, 0), celosia::ui::size, WS_EX_TOPMOST | WS_EX_LAYERED);

    celosia_Win32::D3D::CreateDevice(ui);
    celosia::initialize::context(ui);
	celosia::initialize::fonts();

    celosia_Win32::window::enable_transparency(ui);
    celosia_Win32::window::enable_blur(ui, 4);
    celosia_Win32::window::show(ui);

    bool running = false;
    while (!running)
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = true;
        }

        if (running)
            break;

        celosia::ui::render();
        if(celosia::ui::active)
            celosia_Win32::window::drag();

        BringWindowToTop(ui); // only do this for crosshair overlay
    }

    // unload everything
    celosia_Win32::window::destroy();
	return 0;
}


/* PARALLAX
#include "../include.h"

static int maximum_layers = 4;
static int scale = 125;
static int speed = 5.f;

void celosia::anim::parallax() { // 4 layers maximum, could automate it and make infinite but i am too lazy to rn
	for (int i = 1; i < maximum_layers + 1; i++) { // seems like i did automate it so it is infinite
		float factor = scale / i;
		int diff = maximum_layers - i;

		std::string layer_str = std::to_string(i);
		celosia::anim::smooth("ParallaxMouseXLayer" + layer_str, (ImGui::GetIO().MousePos.x / factor), speed - diff);
		celosia::anim::smooth("ParallaxMouseYLayer" + layer_str, (ImGui::GetIO().MousePos.y / factor), speed - diff);
	}
}
*/

/*
#include "../include.h"
#include <random>
#include <iostream>

struct particle_object{
	int layer = 0;
	bool in_transition = false;
	float alpha = 1.f;
	float next_alpha = 1.f;
	float speed = 10.f;
	ImVec2 position = { 0,0 };
};

static int amount = 1000;
static int radius = 1;
static int parallax_layers = 4;
static int speed_min = 1;
static int speed_max = 4;
ImColor color;

bool initialized = false;
std::map<int, particle_object> particle_objmap;

float randomize(int r1, int r2) { // make this a celosia func
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(r1, r2);
	int random = dist6(rng);
	return (float)random;
}

void initialize_particles() {
	for (int i = 0; i < amount; i++) {
		particle_objmap[i].position = ImVec2{ randomize(0,1920), randomize(0,1080) };
		particle_objmap[i].layer = randomize(1, parallax_layers);
	}
}

void animate_particles() {
	for (int i = 0; i < amount; i++) {

		if (!particle_objmap[i].in_transition) {
			particle_objmap[i].next_alpha = randomize(0, 10) / 10.f;
			particle_objmap[i].speed = randomize(speed_min, speed_max);
			particle_objmap[i].in_transition = true;
		}
		else
			if (particle_objmap[i].alpha != particle_objmap[i].next_alpha) {
				float new_alpha = celosia::anim::smooth("Particle " + std::to_string(i), particle_objmap[i].next_alpha, particle_objmap[i].speed);
				particle_objmap[i].alpha = new_alpha; // ok but get it up _> down and not down -> up
				//particle_objmap[i].alpha = new_alpha * (particle_objmap[i].position.y / 1080); // ok but get it up _> down and not down -> up
			}
			else
				particle_objmap[i].in_transition = false;
	}
}

void render_particles() {
	ImDrawList* backList = ImGui::GetBackgroundDrawList(); // don't get it each frame cache it somewhere

	for (int i = 0; i < amount; i++) { // should be particle_objmap.count but i forgot how that works its been too long
		int layer = particle_objmap[i].layer;
		std::string layer_str = std::to_string(layer);
		float alpha = particle_objmap[i].alpha * celosia::variables::menu::colors::text.Value.w;

		backList->AddCircleFilled(ImVec2(particle_objmap[i].position.x + celosia::anim::map["ParallaxMouseXLayer" + layer_str], particle_objmap[i].position.y + celosia::anim::map["ParallaxMouseYLayer" + layer_str]), radius + (layer / 2), ImColor(color.Value.x, color.Value.y, color.Value.z, alpha));
	}
}

void celosia::anim::particles() {
	if (!initialized) {
		initialize_particles();
		initialized = true;
	}
	color = celosia::variables::menu::colors::theme;
	animate_particles();
	render_particles();
}
*/