#ifndef UTILS_HPP
#define UTILS_HPP
#pragma once

#include <raylib-cpp.hpp>

class Utils {
	public:
		static Vector2 interpolate_vectors(Vector2 a, Vector2 b, double alpha) {
			return Vector2{ (float)(b.x * alpha + a.x * (1.0 - alpha)), (float)(b.y * alpha + a.y * (1.0 - alpha)) };
		}
		static Vector2 subtract_vectors(Vector2 a, Vector2 b) {
			return Vector2{ a.x - b.x, a.y - b.y };
		}
		static Vector2 add_vectors(Vector2 a, Vector2 b) {
			return Vector2{ a.x + b.x, a.y + b.y };
		}
		static Vector2 scale_vector(Vector2 a, double scale) {
			return Vector2{ (float)(a.x * scale), (float)(a.y * scale) };
		}
		static Vector2 window_center() {
			return Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
		}
		static Vector2 normalize_center_to_mouse(float multiplier) {
			return Vector2Multiply(Vector2Normalize(Vector2Subtract(Vector2{ (float) GetMouseX(), (float) GetMouseY() }, Utils::window_center())), Vector2{ multiplier, multiplier });
		}
};

#endif
