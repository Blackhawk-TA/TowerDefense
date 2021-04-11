//
// Created by daniel on 03.04.21.
//

#pragma once
#include <list>
#include "../objects/enemy.hpp"
#include "../utils/map.hpp"

class EnemyHandler {
public:
	static EnemyHandler *getInstance();
	void draw();
	void move();

private:
	static EnemyHandler *instance;
	std::list<Enemy> enemies;
	Timer timer_animate_enemies;

	explicit EnemyHandler();
	static Vec2 calculate_next_position(Vec2 previous_position, Vec2 current_position, map::TileFlags flag);
	static std::vector<Vec2> calculate_path(Vec2 start_position);
	static void animate(Timer &timer);
};