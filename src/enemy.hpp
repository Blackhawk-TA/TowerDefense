//
// Created by daniel on 29.03.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

class Enemy {
public:
	explicit Enemy();
	void draw();

private:
	const Point size = Point(1, 1);
	const Point tile = Point(14, 4);
	const uint8_t velocity = 5;

	uint8_t health;
	Point position;

	void move(Point next_tile);
};
