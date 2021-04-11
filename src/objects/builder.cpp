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
	turn_index = 0;
	sprite_deny_id = 103;
	sprite_allow_id = 104;
	sprite_id = sprite_deny_id;

	uint8_t sprite_arrow_up_id = 31;
	uint8_t sprite_arrow_down_id = 15;
	uint8_t sprite_arrow_left_id = 14;
	uint8_t sprite_arrow_right_id = 30;
	sprite_array_ids = {sprite_arrow_down_id, sprite_arrow_left_id, sprite_arrow_up_id, sprite_arrow_right_id};
}

void Builder::draw() {
	screen.sprite(sprite_id, world_to_screen(position));
	screen.sprite(sprite_id, world_to_screen(position + turn_direction));
	screen.sprite(sprite_array_ids[turn_index], world_to_screen(position + turn_direction));
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
	Point outer_tile_next_position = next_position + turn_direction;

	if (next_position.x >= 0
		&& next_position.y >= 0
		&& next_position.x <= screen_tiles.x
		&& next_position.y <= screen_tiles.y
		&& outer_tile_next_position.x >= 0
		&& outer_tile_next_position.y >= 0
		&& outer_tile_next_position.x <= screen_tiles.x
		&& outer_tile_next_position.y <= screen_tiles.y)
	{
		position = next_position;
		update_sprite();
	}
}

void Builder::turn() {
	Point next_turn_direction;

	turn_index = (turn_index + 1) % 4;
	switch (turn_index) {
		case TurretFacingDirection::UP:
			next_turn_direction = Point(0, -1);
			break;
		case TurretFacingDirection::DOWN:
			next_turn_direction = Point(0, 1);
			break;
		case TurretFacingDirection::LEFT:
			next_turn_direction = Point(-1, 0);
			break;
		case TurretFacingDirection::RIGHT:
			next_turn_direction = Point(1, 0);
			break;
	}

	if (position.x + next_turn_direction.x >= 0
		&& position.y + next_turn_direction.y >= 0
		&& position.x + next_turn_direction.x <= screen_tiles.x
		&& position.y + next_turn_direction.y <= screen_tiles.y)
	{
		turn_direction = next_turn_direction;
		update_sprite();
	} else {
		turn();
	}
}

void Builder::update_sprite() {
	if (map::get_flag(position) == map::TileFlags::BUILDABLE && map::get_flag(position + turn_direction) == map::TileFlags::BUILDABLE) {
		sprite_id = sprite_allow_id;
	} else {
		sprite_id = sprite_deny_id;
	}
}

//TODO figure out which facing_direction is the best
bool Builder::build() {
	//TODO add to occupied + call add_turret of turret_handler
	return false;
}
