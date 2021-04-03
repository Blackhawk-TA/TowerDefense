//
// Created by daniel on 03.04.21.
//

#pragma once
#include "32blit.hpp"
#include "layer_handler.hpp"

class EnemyHandler {
public:
	static std::vector<Point> calculate_path(Point start_position);

private:
	static Point calculate_next_position(Point start_position, LayerHandler::TileFlags flag);
};
