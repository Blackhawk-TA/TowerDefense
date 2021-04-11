//
// Created by Daniel Peters on 08.04.21.
//

#include "turret_handler.hpp"
#include <vector>

using namespace blit;

TurretHandler *TurretHandler::instance = nullptr;

TurretHandler *TurretHandler::getInstance() {
	if (instance == nullptr) {
		instance = new TurretHandler();
	}
	return instance;
}

TurretHandler::TurretHandler() = default;

void TurretHandler::draw() {
	for (Turret &turret : turrets) {
		turret.draw();
	}
}

void TurretHandler::add_turret(Point position, TurretFacingDirection facing_direction) {
	turrets.push_back(*new Turret(position, facing_direction));
}

bool TurretHandler::remove_turret(Point position, TurretFacingDirection facing_direction) {
	auto itr = turrets.begin();
	bool removed = false;
	Point size;

	switch (facing_direction) {
		case TurretFacingDirection::UP:
		case TurretFacingDirection::DOWN:
			size = Point(1, 2);
			break;
		case TurretFacingDirection::LEFT:
		case TurretFacingDirection::RIGHT:
			size = Point(2, 1);
			break;
	}

	while (!removed && itr != turrets.end()) {
		if (itr->get_rect() == Rect(position.x, position.y, size.x, size.y)) {
			turrets.erase(itr++);
			removed = true;
		} else {
			itr++;
		}
	}

	return removed;
}
