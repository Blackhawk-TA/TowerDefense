//
// Created by daniel on 29.03.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Enemy {
public:
	explicit Enemy(Vec2 start_position, std::vector<Vec2> &path);
	void draw();
	void animate(Timer &timer);
	bool move();
	uint8_t take_damage(uint8_t damage);
	Point get_position();

private:
	const uint8_t SPRITE_IDS[3] = {60, 61, 62};
	const float VELOCITY = 0.25;

	SpriteTransform transform;
	int health;
	uint8_t sprite_index;
	uint8_t path_index;
	Vec2 position;
	std::vector<Vec2> path;
};