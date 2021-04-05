//
// Created by daniel on 03.04.21.
//

#include "chest.hpp"

using namespace blit;

Chest::Chest(Point position) {
	Chest::position = position;
	sprite_id = closed_sprite_id;
}

void Chest::draw() {
	screen.sprite(sprite_id, world_to_screen(position));
}

void Chest::open() {
	sprite_id = opened_sprite_id;
}

bool Chest::is_open() {
	return sprite_id == opened_sprite_id;
}

Point Chest::get_position() {
	return position;
}
