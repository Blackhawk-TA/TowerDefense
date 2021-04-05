//
// Created by daniel on 29.03.21.
//

#include "enemy.hpp"

using namespace blit;

Enemy::Enemy(Point start_position, std::vector<Point> &path) {
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
void Enemy::move() {
	if (path_index >= path.size()) {
		return;
	}

	Point next_position = path.at(path_index);
	Vec2 current_position = screen_to_world(position);

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
}
