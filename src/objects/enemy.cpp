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
	screen.sprite(sprite_ids[sprite_index], position, transform);
}

void Enemy::animate(Timer &timer) {
	sprite_index = (sprite_index + 1) % 3;
}

uint8_t Enemy::take_damage(uint8_t &damage) {
	if (health - damage >= 0) {
		health -= damage;
	} else {
		health = 0;
	}

	return health;
}

//TODO current position has rounding issues due to screen_to_world. Works but probably not pixel perfect
bool Enemy::move() {
	if (path_index >= path.size()) {
		return false;
	}

	Vec2 next_position = path.at(path_index);
	Vec2 current_position = screen_to_world(position);

	Chest *chest = ChestHandler::getInstance()->get_by_position(current_position);
	if (chest && !chest->is_open()) {
		chest->open();
		return false;
	}

	if (current_position.x < next_position.x) {
		position.x += velocity;
		transform = SpriteTransform::NONE;
	} else if (current_position.y < next_position.y) {
		position.y += velocity;
	} else if (current_position.x > next_position.x) {
		position.x -= velocity;
		transform = SpriteTransform::HORIZONTAL;
	} else if (current_position.y > next_position.y) {
		position.y -= velocity;
	} else {
		path_index++;
	}

	return true;
}
