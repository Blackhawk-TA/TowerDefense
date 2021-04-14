//
// Created by Daniel Peters on 08.04.21.
//

#include "turret.hpp"
#include "../handlers/enemy_handler.hpp"

using namespace blit;

uint8_t Turret::damage = 10;

Turret::Turret(Point position, TurretFacingDirection facing_direction) {
	Turret::position = position;
	sprite_facing_up = Rect(10, 1, 1, 2);
	sprite_facing_down = Rect(7, 2, 1, 2);
	sprite_facing_left = Rect(8, 2, 2, 1);

	timer_attack.init(attack, 1000, -1);
	timer_attack.start();

	switch (facing_direction) {
		case TurretFacingDirection::UP:
			sprite = sprite_facing_up;
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::DOWN:
			sprite = sprite_facing_down;
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::LEFT:
			sprite = sprite_facing_left;
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::RIGHT:
			sprite = sprite_facing_left;
			transform = SpriteTransform::HORIZONTAL;
			break;
	}
}

void Turret::draw() {
	screen.sprite(sprite, world_to_screen(position), transform);
}

Rect Turret::get_rectangle() const {
	return Rect(position.x, position.y, sprite.w, sprite.h);
}

void Turret::attack(Timer &timer) {
	std::list<Enemy> *enemies = EnemyHandler::getInstance()->get_enemies();
	uint8_t health;
	auto itr = enemies->begin();

	while (itr != enemies->end()) {
		if (in_range(itr->get_position())) {
			health = itr->take_damage(damage);
		}

		if (health == 0) {
			enemies->erase(itr++);
		} else {
			itr++;
		}
	}
}

bool Turret::in_range(Point target) {
	return true; //TODO implement
}
