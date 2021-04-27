//
// Created by daniel on 07.04.21.
//

#include "builder.hpp"
#include "../utils/map.hpp"
#include "../handlers/turret_handler.hpp"

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
	sprite_tile_deny_id = 103;
	sprite_tile_allow_id = 104;
	sprite_tile_id = sprite_tile_deny_id;

	uint8_t sprite_arrow_up_id = 31;
	uint8_t sprite_arrow_down_id = 15;
	uint8_t sprite_arrow_left_id = 14;
	uint8_t sprite_arrow_right_id = 30;
	sprite_arrow_ids = {sprite_arrow_down_id, sprite_arrow_left_id, sprite_arrow_up_id, sprite_arrow_right_id};
}

void Builder::draw() {
	screen.sprite(sprite_tile_id, world_to_screen(position));
	screen.sprite(sprite_tile_id, world_to_screen(position + turn_direction));
	screen.sprite(sprite_arrow_ids[turn_index], world_to_screen(position + turn_direction));
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
		update_tile_sprite();
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
		update_tile_sprite();
	} else {
		turn();
	}
}

bool Builder::is_building_ground() {
	return map::get_flag(position) == map::TileFlags::BUILDABLE
		&& map::get_flag(position + turn_direction) == map::TileFlags::BUILDABLE;
}

bool Builder::can_build() {
	return is_building_ground()
		&& !is_occupied(position)
		&& !is_occupied(position + turn_direction);
}

void Builder::update_tile_sprite() {
	if (can_build()) {
		sprite_tile_id = sprite_tile_allow_id;
	} else {
		sprite_tile_id = sprite_tile_deny_id;
	}
}

bool Builder::is_occupied(Point tile) {
	return occupied_tiles[tile.x][tile.y];
}

void Builder::set_occupied(Point tile, bool value) {
	occupied_tiles[tile.x][tile.y] = value;
	update_tile_sprite();
}

//Calculates the position of the turret which is always on the upper left position
Point Builder::calculate_turret_position() {
	Point turret_spawn_position;

	switch (turn_index) {
		case TurretFacingDirection::DOWN: //base tile i in the upper left
		case TurretFacingDirection::RIGHT:
			turret_spawn_position = position;
			break;
		case TurretFacingDirection::UP: //outer tile is in the upper left
		case TurretFacingDirection::LEFT:
			turret_spawn_position = position + turn_direction;
			break;
	}

	return turret_spawn_position;
}

bool Builder::build() {
	Point outer_tile_position = position + turn_direction;
	Point turret_spawn_position = calculate_turret_position();
	bool build_success = false;

	if (can_build()) {
		TurretHandler::getInstance()->add_turret(turret_spawn_position, (TurretFacingDirection)turn_index);
		set_occupied(position, true);
		set_occupied(outer_tile_position, true);
		build_success = true;
	}

	return build_success;
}

bool Builder::destroy() {
	Point outer_tile_position = position + turn_direction;
	Point turret_spawn_position = calculate_turret_position();
	bool destruction_success = false;

	if (is_building_ground() && is_occupied(position) && is_occupied(outer_tile_position)) {
		if (TurretHandler::getInstance()->remove_turret(turret_spawn_position, (TurretFacingDirection)turn_index)) {
			set_occupied(position, false);
			set_occupied(outer_tile_position, false);
			destruction_success = true;
		}
	}

	return destruction_success;
}

void Builder::reset() {
	for (auto i = 0u; i < occupied_tiles.size(); i++) {
		for (auto j = 0u; j < occupied_tiles.size(); j++) {
			occupied_tiles[i][j] = false;
		}
	}

	//Update build access indicator after resetting occupied tiles
	update_tile_sprite();
}
