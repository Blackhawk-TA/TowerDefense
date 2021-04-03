//
// Created by daniel on 29.03.21.
//

#pragma once
#include "../utils/utils.hpp"
#include "../utils/layer_handler.hpp"

using namespace blit;

class Enemy {
public:
	explicit Enemy(Point start_position, std::vector<Point> &path);
	void draw();
	void move();
	uint8_t take_damage(uint8_t damage);

private:
	const Point size = Point(1, 1);
	const Point sprite = Point(14, 4);
	const uint8_t velocity = 5;

	uint8_t health;
	Point position;
};
