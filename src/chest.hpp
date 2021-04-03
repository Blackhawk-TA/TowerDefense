//
// Created by daniel on 03.04.21.
//

#pragma once

#include "utils/utils.hpp"

using namespace blit;

class Chest {
public:
	Chest(Point position);
	void draw();
	void open();

private:
	const Point size = Point(1, 1);
	const Point closed_sprite = Point(4, 2);
	const Point opened_sprite = Point(5, 2);

	Point sprite;
	Point position;
};
