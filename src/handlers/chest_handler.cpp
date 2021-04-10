//
// Created by daniel on 04.04.21.
//

#include "chest_handler.hpp"

using namespace blit;

ChestHandler *ChestHandler::instance;

ChestHandler *ChestHandler::getInstance() {
	if (instance == nullptr) {
		instance = new ChestHandler();
	}
	return instance;
}

ChestHandler::ChestHandler() {
	for (int i = 0; i < 3; i++) {
		chests.push_back(*new Chest(Point(chest_base_position.x + i, chest_base_position.y)));
	}
}

void ChestHandler::draw() {
	for (Chest &chest : chests) {
		chest.draw();
	}
}

Chest* ChestHandler::get_by_position(Point position) {
	uint8_t i = 0;
	Chest *chest = nullptr;

	while (!chest && i < chests.size()) {
		if (chests.at(i).get_position() == position) {
			chest = &chests.at(i);
		}
		i++;
	}

	return chest;
}
