//
// Created by Daniel Peters on 08.04.21.
//

#pragma once
#include <list>
#include "../utils/utils.hpp"
#include "../game-objects/turret.hpp"

using namespace blit;

class TurretHandler {
public:
	static TurretHandler *getInstance();
	void draw();
	void add_turret(Point position, TurretFacingDirection facing_direction);
	bool remove_turret(Point position, TurretFacingDirection facing_direction);
	void reset();

private:
	static TurretHandler *instance;
	std::list<Turret> turrets;
	Timer timer_attack;
	static Timer *timer_animation;

	explicit TurretHandler();
	static void animate(Timer &timer);
	static void attack(Timer &timer);
	static bool in_range(Point target, Point position, Point range, TurretFacingDirection facing_direction);
	static Timer *get_timer_animation();
};
