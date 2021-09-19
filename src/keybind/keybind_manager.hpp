#ifndef KEYBIND_KEYBIND_MANAGER_HPP
#define KEYBIND_KEYBIND_MANAGER_HPP
#pragma once

#include <raylib-cpp.hpp>
#include <string>
#include <map>

#include "keybind.hpp"

class KeybindManager {
	public:
		std::map<const std::string, Keybind> keybinds;
		void tick() {
			for(auto& keybind : this->keybinds) {
				keybind.second.tick();
			}
		}
		void remove(const std::string& name) {
			this->keybinds.erase(name);
		}
		Keybind& add(const std::string& name, Keybind&& keybind) {
			this->keybinds.insert(std::pair<std::string, Keybind>{ name, keybind });
			return this->get(name);
		}
		Keybind& get(const std::string& name) {
			try {
				return this->keybinds.at(name);
			} catch(std::out_of_range& e) {
				throw std::out_of_range("Keybind \"" + name + "\" doesn't");
			}
		}
		bool is_on(const std::string& name) {
			return this->get(name).is_on();
		}
		bool has(const std::string& name) {
			return this->keybinds.find(name) != this->keybinds.end();
		}
};

#endif