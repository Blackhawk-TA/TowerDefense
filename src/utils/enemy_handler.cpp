//
// Created by daniel on 03.04.21.
//

#include "enemy_handler.hpp"

using namespace blit;

std::vector<Enemy> enemies;
Timer timer_animate_enemies;

void EnemyHandler::spawn_enemies() {
	Point enemy_start_position = Point(0, 1);
	std::vector<Point> enemy_path = EnemyHandler::calculate_path(enemy_start_position);
	enemies.push_back(*new Enemy(enemy_start_position, enemy_path)); //TODO generate enemies automatically

	timer_animate_enemies.init(animate_enemies, 100, -1);
	timer_animate_enemies.start();
}

void EnemyHandler::draw_enemies() {
	for (Enemy &enemy : enemies) {
		enemy.draw();
	}
}

void EnemyHandler::animate_enemies(Timer &timer) {
	for (Enemy &enemy : enemies) {
		enemy.animate(timer);
	}
}

void EnemyHandler::move_enemies() {
	for (Enemy &enemy : enemies) {
		enemy.move();
	}
}

///////////////////////////////////////////////////////////////////////////
//
// Calculates the entire path which all enemies use.
// The path only includes tiles with the 'path' flag, not the 'chest' flag.
//
std::vector<Point> EnemyHandler::calculate_path(Point start_position) {
	std::vector<Point> path;
	Point previous_position = start_position;
	Point current_position = start_position;
	Point next_position;
	bool has_next_position = true;

	while (has_next_position) {
		next_position = calculate_next_position(previous_position, current_position, LayerHandler::PATH);
		if (next_position == current_position) {
			has_next_position = false;
		} else {
			path.push_back(next_position);
			previous_position = current_position;
			current_position = next_position;
		}
	}

	return path;
}

///////////////////////////////////////////////////////////////////////////
//
// Calculates the next position based on current_position.
// TileFlags are used to determine if the enemy can move to a tile.
//
Point EnemyHandler::calculate_next_position(Point previous_position, Point current_position, LayerHandler::TileFlags flag) {
	Point next_position;

	if (LayerHandler::get_flag(current_position + Point(1, 0)) == flag) {
		next_position = current_position + Point(1, 0);
	} else if (LayerHandler::get_flag(current_position + Point(0, 1)) == flag) {
		next_position = current_position + Point(0, 1);
	} else if (LayerHandler::get_flag(current_position - Point(1, 0)) == flag) {
		next_position = current_position - Point(1, 0);
	} else if (LayerHandler::get_flag(current_position - Point(0, 1)) == flag) {
		next_position = current_position - Point(0, 1);
	}

	return next_position == current_position || next_position == previous_position ? current_position : next_position;
}
