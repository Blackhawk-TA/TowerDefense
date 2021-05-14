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
	Point get_barrel_position() const;
	void animate();
	bool is_animation_pending() const;
	void activate_animation_pending();

private:
	const uint8_t damage = 17;
	const std::array<uint8_t, 5> animation_sprite_ids = {0, 56, 57, 58};
	const Point range = Point(1, 4); // How far it can shoot to the left/right and forward
	const Rect sprite_facing_up = Rect(10, 1, 1, 2);
	const Rect sprite_facing_down = Rect(7, 2, 1, 2);
	const Rect sprite_facing_left = Rect(8, 2, 2, 1);

	Point spawn_position;
	Point animation_position;
	Point barrel_position; //The position where the turret fires from
	Rect sprite;
	SpriteTransform transform;
	SpriteTransform animation_transform;
	TurretFacingDirection facing_direction;
	uint8_t animation_sprite_index;
	bool animation_pending;
};
