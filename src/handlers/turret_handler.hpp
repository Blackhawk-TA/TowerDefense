//
// Created by Daniel Peters on 08.04.21.
//

#pragma once
#include <list>
#include "../utils/utils.hpp"
#include "../objects/turret.hpp"

using namespace blit;

class TurretHandler {
public:
	static TurretHandler *getInstance();
	void draw();
	void add_turret(Point position, TurretFacingDirection facing_direction);
	bool remove_turret(Point position, TurretFacingDirection facing_direction);

private:
	static TurretHandler *instance;
	std::list<Turret> turrets;
	Timer timer_attack;

	explicit TurretHandler();
	static void attack(Timer &timer);
	static bool in_range(Point target, TurretFacingDirection facing_direction);
};
