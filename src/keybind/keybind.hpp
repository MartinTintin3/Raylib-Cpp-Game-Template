#ifndef KEYBIND_HPP
#define KEYBIND_HPP
#pragma once

#include <raylib-cpp.hpp>
#include <string>

enum KeybindActivationType {
	TOGGLE,
	ONCE,
	HOLD,
};

enum KeybindType {
	KEYBOARD,
	MOUSE,
};

class Keybind {
	private:
		bool being_pressed = false;
		bool on = false;
		KeyboardKey key;
		MouseButton mouse_button;
		double last_on_time;
	public:
		const std::string description;
		KeybindActivationType activation_type;
		KeybindType type;
		double cooldown = 0;
		Keybind(KeyboardKey key, MouseButton mouse_button, const std::string description, KeybindActivationType activation_type = HOLD, KeybindType type = KEYBOARD, double cooldown = 0): key{ key }, mouse_button{ mouse_button }, description{ description }, activation_type{ activation_type }, type{ type }, cooldown{ cooldown } {
			this->last_on_time = std::numeric_limits<double>::min();
		}
		void tick() {
			const bool is_down = this->type == KEYBOARD ? IsKeyDown(this->key) : IsMouseButtonDown(this->mouse_button);
			const bool is_up = this->type == KEYBOARD ? IsKeyUp(this->key) : IsMouseButtonUp(this->mouse_button);
			switch(this->activation_type) {
				case TOGGLE:
					if(is_down && !this->being_pressed) { 
						this->on = !this->on;
						this->being_pressed = true;
					}
					if(is_up) {
						this->being_pressed = false;
					}
					break;
				case ONCE:
					if(is_down && !this->being_pressed) {
						this->on = true;
						this->being_pressed = true;
					} else if(is_down && this->being_pressed) {
						this->on = false;
					} else if(is_up) {
						this->on = false;
						this->being_pressed = false;
					}
					break;
				case HOLD:
					if(is_down) {
						this->on = true;
						this->being_pressed = true;
					} else if(is_up) {
						this->on = false;
						this->being_pressed = false;
					}
					break;
			}
		}
		bool is_on() {
			if(this->on && GetTime() - this->last_on_time > this->cooldown) {
				this->last_on_time = GetTime();
				return true;
			} else {
				return false;
			}
		}
		bool is_down() {
			return this->type == KEYBOARD ? IsKeyDown(this->key) : IsMouseButtonDown(this->mouse_button);
		}
};

#endif