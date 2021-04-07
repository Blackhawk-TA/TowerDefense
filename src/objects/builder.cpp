//
// Created by daniel on 07.04.21.
//

#include "builder.hpp"
#include "../utils/map.hpp"

using namespace blit;

Builder *Builder::getInstance() {
	if (!instance) {
		instance = new Builder();
	}
	return instance;
}

Builder::Builder() {
	position = Point(0, 0);
	sprite_deny_id = 103;
	sprite_allow_id = 104;
	sprite_id = get_sprite();
}

void Builder::draw() {
	screen.sprite(sprite_id, world_to_screen(position));
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

void Builder::move(Point direction) {
	position += direction;
	sprite_id = get_sprite();
}

uint8_t Builder::get_sprite() {
	if (map::get_flag(screen_to_world(position)) == map::TileFlags::BUILD) {
		return sprite_allow_id;
	} else {
		return sprite_deny_id;
	}
}
