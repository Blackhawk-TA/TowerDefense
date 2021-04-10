//
// Created by Daniel Peters on 08.04.21.
//

#pragma once

#include "../utils/utils.hpp"
#include "../objects/turret.hpp"

using namespace blit;

class TurretHandler {
public:
	static TurretHandler *getInstance();
	void draw();
	void add_turret(Point position, Turret::FacingDirection facing_direction);

private:
	static TurretHandler *instance;
	std::vector<Turret> turrets;

	explicit TurretHandler();
};
