//
// Created by daniel on 03.04.21.
//

#pragma once
#include "32blit.hpp"
#include "layer_handler.hpp"
#include "../objects/enemy.hpp"

class EnemyHandler {
public:
	static void spawn_enemies();
	static void draw_enemies();
	static void animate_enemies(Timer &timer);
	static void move_enemies();

private:
	static Point calculate_next_position(Point previous_position, Point current_position, LayerHandler::TileFlags flag);
	static std::vector<Point> calculate_path(Point start_position);
};
