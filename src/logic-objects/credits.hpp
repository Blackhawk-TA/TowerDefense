//
// Created by daniel on 18.04.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

class Credits {
public:
	static Credits *getInstance();
	void add_kill_reward();
	bool can_buy_turret() const;
	void buy_turret();
	void refund_turret();
	uint32_t get_credits() const;
	void reset();

private:
	const uint8_t START_CREDITS = 30;

	static Credits *instance;
	int credits;
	uint8_t kill_reward;
	uint8_t turret_price;
	float turret_refund_multiplier;

	explicit Credits();
};
