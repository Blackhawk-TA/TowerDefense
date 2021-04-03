//
// Created by daniel on 29.03.21.
//

#include "enemy.hpp"

using namespace blit;

Enemy::Enemy() {
	health = 100;
	position = Point(0, 0);
	has_next_position = false;
};

void Enemy::draw() {
	screen.sprite(Rect(sprite.x, sprite.y, size.x, size.y), world_to_screen(position));
}

uint8_t Enemy::take_damage(uint8_t damage) {
	if (health - damage >= 0) {
		health -= damage;
	} else {
		health = 0;
	}

	return health;
}

void Enemy::move() {
}
