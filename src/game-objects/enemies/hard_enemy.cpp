//
// Created by daniel on 14.05.21.
//

#include "hard_enemy.hpp"

HardEnemy::HardEnemy(Vec2 start_position, std::vector<Vec2> &path) : Enemy(start_position, path) {
	health = 200;
	max_health = 200;
	sprite_ids = {91, 92, 93};
}

Enemy::EnemyType HardEnemy::get_type() {
	return Enemy::HARD;
}
