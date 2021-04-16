//
// Created by Daniel Peters on 08.04.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Turret {
public:
	explicit Turret(Point position, TurretFacingDirection facing_direction);
	void draw();
	Rect get_rectangle() const;
	TurretFacingDirection get_facing_direction();
	uint8_t get_damage() const;
	Point get_range() const;
	Point get_position() const;

private:
	Point position;
	Rect sprite_facing_up;
	Rect sprite_facing_down;
	Rect sprite_facing_left;
	Rect sprite;
	SpriteTransform transform;
	TurretFacingDirection facing_direction;
	uint8_t damage;
	Point range;
};
