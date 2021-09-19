#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once

#include <raylib-cpp.hpp>
#include <string>

#include "constants.hpp"

class Window {
	public:
		Window(std::string title, int width, int height, bool resisable) {
			if(resisable) SetConfigFlags(FLAG_WINDOW_RESIZABLE);
			InitWindow(width, height, title.c_str());
			SetWindowMinSize(MINIMUM_WINDOW_WIDTH, MINIMUM_WINDOW_HEIGHT);
		}
		~Window() {
			CloseWindow(); 
		}
};

#endif