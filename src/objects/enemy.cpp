//
// Created by daniel on 29.03.21.
//

#include "enemy.hpp"

using namespace blit;

Enemy::Enemy(Point start_position, std::vector<Point> &path) {
	health = 100;
	position = world_to_screen(start_position.x, start_position.y);
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

void Enemy::move() {
	position.x += velocity;
}
