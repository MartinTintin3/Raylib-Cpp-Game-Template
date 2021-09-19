#ifndef TPS_COUNTER_HPP
#define TPS_COUNTER_HPP
#pragma once

#include "timer.hpp"

class TPS_Counter {
	private:
		long tps = 0;
		long last_tps = 0;
		long last_time;
	public:
		TPS_Counter(): tps(0), last_tps(0), last_time(floor(GetTime())) {}
		void tick() {
			if(this->last_time != floor(GetTime())) {
				this->last_tps = this->tps;
				this->tps = 1;
				this->last_time = floor(GetTime());
			} else {
				this->tps++;
			}
		}
		long get_tps() {
			return this->last_tps;
		}
};

#endif