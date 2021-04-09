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

void TurretHandler::add_turret(Point position, Turret::FacingDirection facing_direction) {
	turrets.push_back(*new Turret(position, facing_direction));
}
