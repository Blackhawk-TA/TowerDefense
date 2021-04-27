//
// Created by daniel on 03.04.21.
//

#include "chest.hpp"

using namespace blit;

Chest::Chest(Point position) {
	Chest::position = position;
	sprite_id = CLOSED_SPRITE_ID;
}

void Chest::draw() {
	screen.sprite(sprite_id, world_to_screen(position));
}

void Chest::open() {
	sprite_id = OPENED_SPRITE_ID;
}

void Chest::close() {
	sprite_id = CLOSED_SPRITE_ID;
}

bool Chest::is_open() const {
	return sprite_id == OPENED_SPRITE_ID;
}

Point Chest::get_position() {
	return position;
}
