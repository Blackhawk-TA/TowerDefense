//
// Created by Daniel Peters on 08.04.21.
//

#pragma once

#include "../utils/utils.hpp"
#include "../objects/turret.hpp"
#include <vector>

using namespace blit;

class TurretHandler {
public:
	static TurretHandler *getInstance();
	void draw();
	void add_turret(Point position, Turret::FacingDirection facing_direction);

private:
	static TurretHandler *instance;
	explicit TurretHandler();

	std::vector<Turret> turrets;
};
