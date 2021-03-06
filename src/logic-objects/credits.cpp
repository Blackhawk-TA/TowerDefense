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
	credits = START_CREDITS;
}

void Credits::add_kill_reward(Enemy::EnemyType enemy_type) {
	switch (enemy_type) {
		case Enemy::EASY:
			credits += EASY_KILL_REWARD;
			break;
		case Enemy::MEDIUM:
			credits += MEDIUM_KILL_REWARD;
			break;
		case Enemy::HARD:
			credits += HARD_KILL_REWARD;
			break;
	}
}

bool Credits::can_buy_turret() const {
	return credits - TURRET_PRICE >= 0;
}

void Credits::buy_turret() {
	credits -= TURRET_PRICE;
}

void Credits::refund_turret() {
	credits += static_cast<int>(static_cast<float>(TURRET_PRICE) * TURRET_REFUND_MULTIPLIER);
}

uint32_t Credits::get_credits() const {
	return credits;
}

void Credits::reset() {
	credits = START_CREDITS;
}
