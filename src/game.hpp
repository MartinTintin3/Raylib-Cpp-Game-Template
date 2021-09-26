#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <memory>
#include <string>

#include "window.hpp"
#include "counter.hpp"
#include "keybind/keybind_manager.hpp"

class Game {
	public:
		Game(std::string title);
		~Game();
		void destroy();
		Camera2D camera;
		bool paused = false;
		KeybindManager keybind_manager;
	private:
		TPS_Counter tps_counter;
		std::unique_ptr<Window> window;
		void register_keybinds();
		void loop();
		void tick(const double& delta);
		void render(const double& alpha);
		void handle_input(const double& delta);
		void setup_camera(Camera2D& camera);
		void update_camera(const double& alpha);
};

#endif
