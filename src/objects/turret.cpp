//
// Created by Daniel Peters on 08.04.21.
//

#include "turret.hpp"

using namespace blit;


Turret::Turret(Point position, TurretFacingDirection facing_direction) {
	Turret::spawn_position = position;
	Turret::facing_direction = facing_direction;
	range = Point(1, 3);
	damage = 10;
	sprite_facing_up = Rect(10, 1, 1, 2);
	sprite_facing_down = Rect(7, 2, 1, 2);
	sprite_facing_left = Rect(8, 2, 2, 1);

	switch (facing_direction) {
		case TurretFacingDirection::UP:
			sprite = sprite_facing_up;
			barrel_position = spawn_position;
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::DOWN:
			sprite = sprite_facing_down;
			barrel_position = spawn_position + Point(0, 1);
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::LEFT:
			sprite = sprite_facing_left;
			barrel_position = spawn_position;
			transform = SpriteTransform::NONE;
			break;
		case TurretFacingDirection::RIGHT:
			sprite = sprite_facing_left;
			barrel_position = spawn_position + Point(1, 0);
			transform = SpriteTransform::HORIZONTAL;
			break;
	}
}

void Turret::draw() {
	screen.sprite(sprite, world_to_screen(spawn_position), transform);
}

Rect Turret::get_rectangle() const {
	return Rect(spawn_position.x, spawn_position.y, sprite.w, sprite.h);
}

TurretFacingDirection Turret::get_facing_direction() {
	return facing_direction;
}

uint8_t Turret::get_damage() const {
	return damage;
}

Point Turret::get_range() const {
	return range;
}

Point Turret::get_barrel_position() const {
	return barrel_position;
}

void Turret::animate(Timer &timer) {

}
