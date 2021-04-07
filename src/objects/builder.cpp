//
// Created by daniel on 07.04.21.
//

#include "builder.hpp"
#include "../utils/map.hpp"

using namespace blit;

Builder *Builder::instance = nullptr;

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
	sprite_id = sprite_deny_id;
	buildable = false;
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

	buildable = check_build_permission();
	if (buildable) {
		sprite_id = sprite_allow_id;
	} else {
		sprite_id = sprite_deny_id;
	}
}

bool Builder::check_build_permission() {
	return map::get_flag(position) == map::TileFlags::BUILDABLE;
}
