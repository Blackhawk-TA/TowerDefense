//
// Created by daniel on 03.04.21.
//

#include "chest.hpp"

using namespace blit;

Chest::Chest(Point position) {
	Chest::position = position;
	sprite = closed_sprite;
}

void Chest::draw() {
	screen.sprite(Rect(sprite.x, sprite.y, size.x, size.y), world_to_screen(position));
}

void Chest::open() {
	sprite = opened_sprite;
}
