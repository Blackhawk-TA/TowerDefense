//
// Created by daniel on 14.05.21.
//

#include "medium_enemy.hpp"

MediumEnemy::MediumEnemy(Vec2 start_position, std::vector<Vec2> &path) {
	health = 150;
	max_health = 150;
	sprite_ids = {75, 76, 77};

	Enemy::path = path;
	position = world_to_screen(start_position.x, start_position.y);
	health_bar_size = TILE_SIZE;
	path_index = 0;
	sprite_index = 0;
	transform = SpriteTransform::NONE;
}
