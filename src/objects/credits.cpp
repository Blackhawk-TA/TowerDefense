//
// Created by daniel on 18.04.21.
//

#include "credits.hpp"

Credits *Credits::instance = nullptr;

Credits *Credits::getInstance() {
	if (instance == nullptr) {
		instance = new Credits();
	}
	return instance;
}

Credits::Credits() {
	credits = 15;
	kill_reward = 10;
	turret_price = 15;
	turret_refund_multiplier = 0.75;
}

void Credits::add_kill_reward() {
	credits += kill_reward;
}

bool Credits::can_buy_turret() const {
	return credits - turret_price >= 0;
}

void Credits::buy_turret() {
	credits -= turret_price;
}

void Credits::refund_turret() {
	credits += turret_price * turret_refund_multiplier;
}

uint32_t Credits::get_credits() const {
	return credits;
}
