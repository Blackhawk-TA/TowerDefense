//
// Created by daniel on 07.04.21.
//

#include "builder.hpp"
#include "../utils/map.hpp"

using namespace blit;

Builder *Builder::instance = nullptr;

Builder *Builder::getInstance() {
	if (instance == nullptr) {
		instance = new Builder();
	}
	return instance;
}

Builder::Builder() {
	position = Point(0, 0);
	turn_direction = Point(0, 1);
	build_vertical = true;
	sprite_deny_id = 103;
	sprite_allow_id = 104;
	sprite_id = sprite_deny_id;
}

void Builder::draw() {
	screen.sprite(sprite_id, world_to_screen(position));
	screen.sprite(sprite_id, world_to_screen(position + turn_direction));
}

void Builder::move_up() {
	move(Point(0, -1));
}

void Builder::move_down() {
	move(Point(0, 1));
}

void Builder::move_left() {
	move(Point(-1, 0));
}

void Builder::move_right() {
	move(Point(1, 0));
}

void Builder::move(Point movement) {
	Point next_position = position + movement;
	Point tile_two_next_position = position + turn_direction + movement;

	if (next_position.x >= 0 && next_position.y >= 0
		&& tile_two_next_position.x <= screen_tiles.x
		&& tile_two_next_position.y <= screen_tiles.y)
	{
		position = next_position;
		update_sprite();
	}
}

void Builder::turn() {
	Point next_turn_direction;

	if (build_vertical) {
		next_turn_direction = Point(1, 0);
	} else {
		next_turn_direction = Point(0, 1);
	}

	if (position.x + next_turn_direction.x <= screen_tiles.x && position.y + next_turn_direction.y <= screen_tiles.y) {
		turn_direction = next_turn_direction;
		build_vertical = !build_vertical;
		update_sprite();
	}
}

void Builder::update_sprite() {
	if (map::get_flag(position) == map::TileFlags::BUILDABLE && map::get_flag(position + turn_direction) == map::TileFlags::BUILDABLE) {
		sprite_id = sprite_allow_id;
	} else {
		sprite_id = sprite_deny_id;
	}
}
