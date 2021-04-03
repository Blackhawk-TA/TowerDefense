//
// Created by daniel on 03.04.21.
//

#pragma once
#include "32blit.hpp"
#include "layer_handler.hpp"
#include "../objects/enemy.hpp"

class EnemyHandler {
public:
	explicit EnemyHandler(Point enemy_start_position);
	void spawn_enemies();
	void draw_enemies();
	void move_enemies();

private:
	Point enemy_start_position;
	std::vector<Enemy> enemies;

	static Point calculate_next_position(Point previous_position, Point current_position, LayerHandler::TileFlags flag);
	static std::vector<Point> calculate_path(Point start_position);
};
