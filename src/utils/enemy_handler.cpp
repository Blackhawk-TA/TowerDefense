//
// Created by daniel on 03.04.21.
//

#include "enemy_handler.hpp"

using namespace blit;

///////////////////////////////////////////////////////////////////////////
//
// Calculates the entire path which all enemies use.
// The path only includes tiles with the 'path' flag, not the 'chest' flag.
//
std::vector<Point> EnemyHandler::calculate_path(Point start_position) {
	std::vector<Point> path;
	Point current_position = start_position;
	Point next_position;
	bool has_next_position = true;

	while (has_next_position) {
		next_position = calculate_next_position(current_position, LayerHandler::PATH);
		if (next_position == current_position) {
			has_next_position = false;
		} else {
			path.push_back(next_position);
			current_position = next_position;
		}
	}

	return path;
}

///////////////////////////////////////////////////////////////////////////
//
// Calculates the next position based on start_position.
// TileFlags are used to determine if the enemy can move to a tile.
//
Point EnemyHandler::calculate_next_position(Point start_position, LayerHandler::TileFlags flag) {
	if (LayerHandler::get_flag(start_position + Point(1, 0)) == flag) {
		return start_position + Point(1, 0);
	} else if (LayerHandler::get_flag(start_position + Point(0, 1)) == flag) {
		return start_position + Point(0, 1);
	} else if (LayerHandler::get_flag(start_position - Point(1, 0)) == flag) {
		return start_position - Point(1, 0);
	} else if (LayerHandler::get_flag(start_position - Point(0, 1)) == flag) {
		return start_position - Point(0, 1);
	}

	return start_position;
}
