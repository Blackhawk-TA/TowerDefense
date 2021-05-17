//
// Created by daniel on 18.04.21.
//

#pragma once
#include "32blit.hpp"
#include "../game-objects/enemy.hpp"

using namespace blit;

class Credits {
public:
	static Credits *getInstance();
	void add_kill_reward(Enemy::EnemyType enemy_type);
	bool can_buy_turret() const;
	void buy_turret();
	void refund_turret();
	uint32_t get_credits() const;
	void reset();

private:
	const uint8_t START_CREDITS = 150;
	const uint8_t EASY_KILL_REWARD = 15;
	const uint8_t MEDIUM_KILL_REWARD = 20;
	const uint8_t HARD_KILL_REWARD = 25;
	const uint8_t TURRET_PRICE = 25;
	const float TURRET_REFUND_MULTIPLIER = 0.75;

	static Credits *instance;
	int credits;

	explicit Credits();
};
