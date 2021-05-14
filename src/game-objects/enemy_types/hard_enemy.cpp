//
// Created by daniel on 14.05.21.
//

#include "hard_enemy.hpp"

HardEnemy::HardEnemy(Vec2 start_position, std::vector<Vec2> &path) {
	health = 200;
	max_health = 200;
	sprite_ids = {91, 92, 93};

	Enemy::path = path;
	position = world_to_screen(start_position.x, start_position.y);
	health_bar_size = TILE_SIZE;
	path_index = 0;
	sprite_index = 0;
	transform = SpriteTransform::NONE;
}
