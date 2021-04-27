//
// Created by daniel on 04.04.21.
//

#include "chest_handler.hpp"

using namespace blit;

ChestHandler *ChestHandler::instance = nullptr;

ChestHandler *ChestHandler::getInstance() {
	if (instance == nullptr) {
		instance = new ChestHandler();
	}
	return instance;
}

ChestHandler::ChestHandler() {
	has_closed_chest = true;

	for (int i = 0; i < 3; i++) {
		chests.push_back(*new Chest(Point(chest_base_position.x + i, chest_base_position.y)));
	}
}

bool ChestHandler::get_has_closed_chest() const {
	return has_closed_chest;
}

void ChestHandler::draw() {
	for (Chest &chest : chests) {
		chest.draw();
	}
}

bool ChestHandler::open_by_position(Point position) {
	Chest *chest = get_by_position(position);
	bool opened = false;

	if (chest && !chest->is_open()) {
		chest->open();
		opened = true;
		check_closed_chests();
	}

	return opened;
}

void ChestHandler::reset() {
	for (Chest &chest : chests) {
		chest.close();
	}

	has_closed_chest = true;
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

void ChestHandler::check_closed_chests() {
	size_t i = 0;
	has_closed_chest = false;

	while (!has_closed_chest && i < chests.size()) {
		if (!chests.at(i).is_open()) {
			has_closed_chest = true;
		}
		i++;
	}
}
