//
// Created by daniel on 29.03.21.
//

#include "enemy.hpp"
#include "../handlers/chest_handler.hpp"

using namespace blit;

Enemy::Enemy(Vec2 start_position, std::vector<Vec2> &path) {
	Enemy::path = path;
	position = world_to_screen(start_position.x, start_position.y);
	health = 100;
	path_index = 0;
	sprite_index = 0;
	transform = SpriteTransform::NONE;
}

void Enemy::draw() {
	screen.sprite(SPRITE_IDS[sprite_index], position, transform);
}

void Enemy::animate(Timer &timer) {
	sprite_index = (sprite_index + 1) % 3;
}

uint8_t Enemy::take_damage(uint8_t damage) {
	if (health - damage >= 0) {
		health -= damage;
	} else {
		health = 0;
	}

	return health;
}

bool Enemy::move() {
	if (path_index >= path.size()) {
		return false;
	}

	Vec2 next_position = path.at(path_index);
	Vec2 current_position = screen_to_world(position);

	bool chest_opened = ChestHandler::getInstance()->open_by_position(current_position);
	if (chest_opened) {
		return false;
	}

	if (current_position.x < next_position.x) {
		position.x += VELOCITY;
		transform = SpriteTransform::NONE;
	} else if (current_position.y < next_position.y) {
		position.y += VELOCITY;
	} else if (current_position.x > next_position.x) {
		position.x -= VELOCITY;
		transform = SpriteTransform::HORIZONTAL;
	} else if (current_position.y > next_position.y) {
		position.y -= VELOCITY;
	} else {
		path_index++;
	}

	return true;
}

Point Enemy::get_position() {
	return screen_to_world(position);
}
