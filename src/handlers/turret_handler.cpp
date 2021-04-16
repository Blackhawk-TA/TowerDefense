//
// Created by Daniel Peters on 08.04.21.
//

#include "turret_handler.hpp"
#include "../objects/enemy.hpp"
#include "enemy_handler.hpp"
#include <vector>

using namespace blit;

TurretHandler *TurretHandler::instance = nullptr;

TurretHandler *TurretHandler::getInstance() {
	if (instance == nullptr) {
		instance = new TurretHandler();
	}
	return instance;
}

TurretHandler::TurretHandler() {
	timer_attack.init(attack, 1000, -1);
	timer_attack.start();
}

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
		if (itr->get_rectangle() == Rect(position.x, position.y, size.x, size.y)) {
			turrets.erase(itr++);
			removed = true;
		} else {
			itr++;
		}
	}

	return removed;
}

void TurretHandler::attack(Timer &timer) {
	std::list<Turret> *turrets = &TurretHandler::getInstance()->turrets;
	std::list<Enemy> *enemies = EnemyHandler::getInstance()->get_enemies();
	uint8_t health;
	Point enemy_position;
	Point turret_position;
	Point turret_range;
	TurretFacingDirection facing_direction;

	for (Turret &turret : *turrets) {
		auto itr = enemies->begin();
		turret_range = turret.get_range();
		turret_position = turret.get_position();
		facing_direction = turret.get_facing_direction();

		while (itr != enemies->end()) {
			enemy_position = itr->get_position();

			if (in_range(enemy_position, turret_position, turret_range, facing_direction)) {
				health = itr->take_damage(turret.get_damage());
			}

			if (health == 0) {
				enemies->erase(itr++);
			} else {
				itr++;
			}
		}
	}
}

bool TurretHandler::in_range(Point target, Point position, Point range, TurretFacingDirection facing_direction) {
	bool is_in_range = false;

	switch (facing_direction) {
		case TurretFacingDirection::UP:
			break;
		case TurretFacingDirection::DOWN:
			break;
		case TurretFacingDirection::LEFT:
			break;
		case TurretFacingDirection::RIGHT:
			break;
	}

	return is_in_range;
}
