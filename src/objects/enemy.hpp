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
	uint8_t take_damage(uint8_t &damage);

private:
	const uint8_t sprite_ids[3] = {60, 61, 62};
	const float velocity = 0.25;

	SpriteTransform transform;
	uint8_t sprite_index;
	uint8_t health;
	uint8_t path_index;
	Vec2 position;
	std::vector<Vec2> path;
};
