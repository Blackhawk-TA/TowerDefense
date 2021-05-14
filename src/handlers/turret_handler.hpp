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
	void stop_timer_attack();
	void reset();

private:
	static TurretHandler *instance;
	static const int ATTACK_INTERVAL = 1000;
	static const int ANIMATION_INTERVAL = 100;
	std::list<Turret> turrets;
	Timer timer_attack;
	static Timer *timer_animation;

	explicit TurretHandler();
	static void animate(Timer &timer);
	static void attack(Timer &timer);
	static bool in_range(Point target, Point position, Point range, TurretFacingDirection facing_direction);
	static Timer *get_timer_animation();
};
