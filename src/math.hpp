#ifndef MATH_HPP
#define MATH_HPP
#pragma once

class Math {
	public:
		static inline double degrees_to_radians(double degrees) {
			return degrees * (PI / 180);
		}
		static inline double radians_to_degrees(double radians) {
			return radians * (180 / PI);
		}
};

#endif