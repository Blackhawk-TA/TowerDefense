//
// Created by daniel on 14.05.21.
//

#include "easy_enemy.hpp"

EasyEnemy::EasyEnemy(Vec2 start_position, std::vector<Vec2> &path) {
	health = 100;
	max_health = 100;
	sprite_ids = {60, 61, 62};

	Enemy::path = path;
	position = world_to_screen(start_position.x, start_position.y);
	health_bar_size = TILE_SIZE;
	path_index = 0;
	sprite_index = 0;
	transform = SpriteTransform::NONE;
}

Enemy::EnemyType EasyEnemy::get_type() {
	return EnemyType::EASY;
}
