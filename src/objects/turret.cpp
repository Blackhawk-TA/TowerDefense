//
// Created by Daniel Peters on 08.04.21.
//

#include "turret.hpp"

using namespace blit;

Turret::Turret(Point position, TurretFacingDirection facing_direction) {
	Turret::position = position;
	sprite_facing_up = Rect(10, 1, 1, 2);
	sprite_facing_down = Rect(7, 2, 1, 2);
	sprite_facing_left = Rect(8, 2, 2, 1);

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
