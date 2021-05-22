//
// Created by daniel on 29.03.21.
//

#pragma once
#include "../../utils/utils.hpp"

using namespace blit;

class Enemy {
public:
	enum EnemyType {
		EASY,
		MEDIUM,
		HARD
	};

	Enemy(Vec2 start_position, std::vector<Vec2> &path);
	void draw();
	void animate(Timer &timer);
	bool move();
	uint8_t take_damage(uint8_t damage);
	Point get_position();
	virtual EnemyType get_type();

protected:
	const float VELOCITY = 0.25;

	SpriteTransform transform;
	int health;
	float max_health;
	std::array<uint8_t, 3> sprite_ids{};
	uint8_t health_bar_size;
	uint8_t sprite_index;
	uint8_t path_index;
	Vec2 position;
	std::vector<Vec2> path;
};
