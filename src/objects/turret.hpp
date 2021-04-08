//
// Created by Daniel Peters on 08.04.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Turret {
public:
	enum FacingDirection {
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};
	explicit Turret(Point position, FacingDirection facing_direction);
	void draw();

private:
	Point position;
	Rect sprite_facing_up;
	Rect sprite_facing_down;
	Rect sprite_facing_left;
	Rect sprite;
	SpriteTransform transform;
};
