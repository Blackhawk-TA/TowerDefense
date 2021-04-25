//
// Created by Daniel Peters on 08.04.21.
//

#include "turret_handler.hpp"
#include "../logic-objects/credits.hpp"
#include "../game-objects/enemy.hpp"
#include "enemy_handler.hpp"
#include <vector>

using namespace blit;

TurretHandler *TurretHandler::instance = nullptr;
Timer *TurretHandler::timer_animation = nullptr;

TurretHandler *TurretHandler::getInstance() {
	if (instance == nullptr) {
		instance = new TurretHandler();
	}
	return instance;
}

TurretHandler::TurretHandler() {
	timer_attack.init(attack, 1000, -1);
	timer_attack.start();

	TurretHandler::get_timer_animation()->init(animate, 100, 3);
}

Timer *TurretHandler::get_timer_animation() {
	if (timer_animation == nullptr) {
		timer_animation = new Timer();
	}
	return timer_animation;
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
	bool take_damage = false;
	uint8_t health;
	Point enemy_position;
	Point turret_position;
	Point turret_range;
	TurretFacingDirection facing_direction;

	for (Turret &turret : *turrets) {
		auto itr = enemies->begin();
		turret_range = turret.get_range();
		turret_position = turret.get_barrel_position();
		facing_direction = turret.get_facing_direction();

		//TODO check if firing at only one target at once is working
		while (!turret.is_animation_pending() && itr != enemies->end()) {
			enemy_position = itr->get_position();

			if (in_range(enemy_position, turret_position, turret_range, facing_direction)) {
				health = itr->take_damage(turret.get_damage());
				take_damage = true;
				turret.activate_animation_pending();
			}

			//Kill enemy
			if (take_damage && health == 0) {
				enemies->erase(itr++);
				Credits::getInstance()->add_kill_reward();
				take_damage = false;
			} else {
				itr++;
			}
		}
	}

	//Animate turret shots
	TurretHandler::get_timer_animation()->start();
}

void TurretHandler::animate(Timer &timer) {
	for (Turret &turret : TurretHandler::getInstance()->turrets) {
		if (turret.is_animation_pending()) {
			turret.animate();
		}
	}
}

bool TurretHandler::in_range(Point target, Point position, Point range, TurretFacingDirection facing_direction) {
	bool is_in_range = false;

	switch (facing_direction) {
		case TurretFacingDirection::UP:
			if (position.y - target.y <= range.y && position.y - target.y >= 0
				&& position.x - target.x <= range.x && position.x - target.x >= -range.x) {
				is_in_range = true;
			}
			break;
		case TurretFacingDirection::DOWN:
			if (position.y - target.y >= -range.y && position.y - target.y <= 0
				&& position.x - target.x <= range.x && position.x - target.x >= -range.x) {
				is_in_range = true;
			}
			break;
		case TurretFacingDirection::LEFT:
			if (position.x - target.x <= range.y && position.x - target.x >= 0
				&& position.y - target.y <= range.x && position.y - target.y >= -range.x) {
				is_in_range = true;
			}
			break;
		case TurretFacingDirection::RIGHT:
			if (position.x - target.x >= -range.y && position.x - target.x <= 0
				&& position.y - target.y <= range.x && position.y - target.y >= -range.x) {
				is_in_range = true;
			}
			break;
	}

	return is_in_range;
}
