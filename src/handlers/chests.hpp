//
// Created by daniel on 04.04.21.
//

#pragma once

#include "../objects/chest.hpp"

namespace chests {
	void create();
	void draw();
	Chest* get_by_position(Point position);
}
