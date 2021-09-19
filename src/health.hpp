#ifndef HEALTH_HPP
#define HEALTH_HPP
#pragma once

#include <string>
#include <iostream>

class Health {
	private:
		unsigned int max_health;
		unsigned int current_health;
	public:
		Health(unsigned int max_health, unsigned int current_health): max_health{ max_health }, current_health{ current_health } {
			if (this->current_health > this->max_health) this->current_health = this->max_health;
		}
		Health(unsigned int max_health): max_health{ max_health }, current_health{ max_health } {}
		unsigned int get_current_health() { return this->current_health; }
		unsigned int get_max_health() { return this->max_health; }
		void set_current_health(const unsigned int& current_health) {
			this->current_health = current_health;
			if(this->current_health > this->max_health) this->current_health = this->max_health;
		}
		void set_max_health(const unsigned int& max_health) { this->max_health = max_health; };
		unsigned int take_damage(const unsigned int& damage) {
			this->current_health -= damage;
			if(this->current_health < 0) this->current_health = 0;
			return this->current_health;
		}
		unsigned int heal(const unsigned int& heal) {
			this->current_health += heal;
			if(this->current_health > this->max_health) this->current_health = this->max_health;
			return this->current_health;
		}
		std::string to_string(std::string prepend = "", std::string append = "") {
			return prepend + std::to_string(this->current_health) + "/" + std::to_string(this->max_health) + append;
		}
};

#endif