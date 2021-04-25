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
	Point spawn_position;
	Point animation_position;
	Point barrel_position; //The position where the turret fires from
	Point range; // How far it can shoot to the left/right and forward
	Rect sprite_facing_up;
	Rect sprite_facing_down;
	Rect sprite_facing_left;
	Rect sprite;
	SpriteTransform transform;
	SpriteTransform animation_transform;
	std::array<uint8_t, 5> animation_sprite_ids{};
	TurretFacingDirection facing_direction;
	uint8_t animation_sprite_index;
	uint8_t damage;
	bool animation_pending;
};
