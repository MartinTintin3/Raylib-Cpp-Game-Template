#include "game.hpp"

#include <raylib-cpp.hpp>

#include "counter.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "math.hpp"
#include "keybind/keybind.hpp"

#define TARGET_TPS 20

Game::Game(std::string title):
		camera{ }, keybind_manager{ }, tps_counter{ },
		window(new Window{ title, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, true }) {
	SetTargetFPS(120);

	this->setup_camera(this->camera);

	this->register_keybinds();
	this->loop();
	this->destroy();
};

void Game::register_keybinds() {
	// Constructor of Keybind takes a keyboard key and a mouse button, which can be toggled between each other, a description, the keybind type, and the mode(KEYBOARD or MOUSE)
	/* Example of 3 types of keybinds */
	// 1. HOLD -> When key down, keybind is activated, and it is deactivated when key is released
	// TODO: Add example for keybind type HOLD
	// 2. ONCE -> When key is pressed, keybind is activated and deactivated on the next tick
	// TODO: Add example for keybind type ONCE
	// 3. TOGGLE -> When key is down, the keybind is activated, and when key is released and pressed again, the keybind is deactivated
	this->keybind_manager.add("pause", Keybind{ KEY_P, MOUSE_LEFT_BUTTON, "Pause", TOGGLE, KEYBOARD });
}

void Game::loop() {
	constexpr double timestep = 1.0 / TARGET_TPS;

	double accumulator = 0.0;
	double alpha_before_pause = 0.0;
	double current_time = GetTime();
	Keybind& pause_keybind = keybind_manager.get("pause");
	// bool paused_from_focus = false;

	while(!WindowShouldClose()) {
		double new_time = GetTime();
		double frame_time = new_time - current_time;
		current_time = GetTime();

		accumulator += frame_time;

		while(accumulator >= timestep) {
			keybind_manager.tick();
			this->paused = pause_keybind.is_on();
			/*if(!IsWindowFocused()) {
				this->paused = true;
				paused_from_focus = true;
			} else if(IsWindowFocused() && paused_from_focus && !pause_keybind.is_on()) {
				this->paused = false;
				paused_from_focus = false;
			}*/
			if(!this->paused) this->update_interpolation();
			if(!this->paused) this->handle_input(timestep);
			if(!this->paused) this->tick(timestep);
			accumulator -= timestep;
		}

		auto alpha = (double)(accumulator / timestep);
		if(!this->paused) alpha_before_pause = alpha;

		this->render(alpha_before_pause);
	}
}

void Game::destroy() {
	// Handle the destruction of the game
	this->window.reset();
}

void Game::tick(const double& delta) {
	this->tps_counter.tick();
	// All of the game logic should be calculate here, and movement/position change should be multiplied by delta
}

void Game::render(const double& alpha) {
	this->update_camera(alpha);
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawLineEx(Utils::window_center(), Vector2Add(Utils::window_center(), Utils::normalize_center_to_mouse(40.0f * this->camera.zoom)), 8.0f, BLACK);
		BeginMode2D(this->camera);
			// Render everything here using the alpha value as the parameter for the entity's render method
		EndMode2D();
		// HUD
		if(this->paused) {
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 100 });
			DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 30) / 2, GetScreenHeight() / 2 - 15, 30, RAYWHITE);
		}
		// DrawFPS(10, 10);
	EndDrawing();
}

void Game::handle_input(const double& delta) {
	// Handle all keybinds using this->keybind_manager.is_on("keybind_name") and use delta for movement/position change
}

void Game::update_interpolation() {
	// Update every entity's previous_position to be the current position for interpolation
}

void Game::setup_camera(Camera2D& camera) {
	// Setup camera's target, offset, and zoom
	// this->camera.target = { this->target.position.x + this->target.size.x / 2, this->target.position.y + this->target.size.y / 2 };
	// this->camera.offset = Vector2{ ((float) GetScreenWidth()) / 2, ((float) GetScreenHeight()) / 2 };
	// this->camera.zoom = 1.0f;
}

void Game::update_camera(const double& alpha) {
	// Update camera's target, offset, and zoom based on interpolated position, screen width / height, and screen height / initial window height
	// const Vector2 interpolated = this->target.interpolate(alpha);
	// this->camera.target = { interpolated.x + this->target.size.x / 2, interpolated.y + this->target.size.y / 2 };
	// this->camera.offset = Vector2{ ((float) GetScreenWidth()) / 2, ((float) GetScreenHeight()) / 2 };
}

Game::~Game() {
	this->destroy();
}
