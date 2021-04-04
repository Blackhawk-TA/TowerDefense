//
// Created by daniel on 29.03.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Enemy {
public:
	explicit Enemy(Point start_position, std::vector<Point> &path);
	void draw();
	void animate(Timer &timer);
	void move();
	uint8_t take_damage(uint8_t &damage);

private:
	const uint8_t sprite_ids[6] = {60, 61, 62};
	const float velocity = 0.5;

	SpriteTransform transform;
	uint8_t sprite_index;
	uint8_t health;
	Vec2 position;
};
