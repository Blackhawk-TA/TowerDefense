//
// Created by daniel on 14.05.21.
//

#include "medium_enemy.hpp"

MediumEnemy::MediumEnemy(Vec2 start_position, std::vector<Vec2> &path) : Enemy(start_position, path) {
	health = 150;
	max_health = 150;
	sprite_ids = {75, 76, 77};
}

Enemy::EnemyType MediumEnemy::get_type() {
	return Enemy::MEDIUM;
}
