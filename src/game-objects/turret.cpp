//
// Created by Daniel Peters on 08.04.21.
//

#include "turret.hpp"

using namespace blit;

Turret::Turret(Point position, TurretFacingDirection facing_direction) {
	Turret::spawn_position = position;
	Turret::facing_direction = facing_direction;

	range = Point(1, 4);
	damage = 12;

	animation_pending = false;
	animation_sprite_ids = {0, 56 ,57, 58};
	animation_sprite_index = 0;
	animation_transform = SpriteTransform::NONE;

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
	screen.sprite(animation_sprite_ids[animation_sprite_index], world_to_screen(animation_position), animation_transform);
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

void Turret::animate() {
	if (!animation_pending) {
		return;
	}

	switch (facing_direction) {
		case TurretFacingDirection::UP:
			animation_transform = SpriteTransform::R90;
			animation_position = barrel_position + Point(0, -1);
			break;
		case TurretFacingDirection::DOWN:
			animation_transform = SpriteTransform::R270;
			animation_position = barrel_position + Point(0, 1);
			break;
		case TurretFacingDirection::LEFT:
			animation_transform = SpriteTransform::NONE;
			animation_position = barrel_position + Point(-1, 0);
			break;
		case TurretFacingDirection::RIGHT:
			animation_transform = SpriteTransform::R180;
			animation_position = barrel_position + Point(1, 0);
			break;
	}

	if (animation_sprite_index < animation_sprite_ids.size() - 1) {
		animation_sprite_index++;
	} else {
		animation_sprite_index = 0;
		animation_pending = false;
	}
}

bool Turret::is_animation_pending() const {
	return animation_pending;
}

void Turret::activate_animation_pending() {
	animation_pending = true;
}
