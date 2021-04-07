//
// Created by daniel on 03.04.21.
//

#include <list>
#include "enemies.hpp"
#include "../objects/enemy.hpp"
#include "../utils/map.hpp"

using namespace blit;

namespace enemies {
	std::list<Enemy> enemies;
	Timer timer_animate_enemies;

	///////////////////////////////////////////////////////////////////////////
	//
	// Calculates the next position based on current_position.
	// TileFlags are used to determine if the enemy can move to a tile.
	//
	Vec2 calculate_next_position(Vec2 previous_position, Vec2 current_position, map::TileFlags flag) {
		Vec2 next_position = current_position; //If next position stays current position, there are no further flags

		if (previous_position != current_position + Point(1, 0) && map::get_flag(current_position + Vec2(1, 0)) == flag) {
			next_position = current_position + Vec2(1, 0);
		} else if (previous_position != current_position + Point(0, 1) && map::get_flag(current_position + Vec2(0, 1)) == flag) {
			next_position = current_position + Vec2(0, 1);
		} else if (previous_position != current_position - Point(1, 0) && map::get_flag(current_position - Vec2(1, 0)) == flag) {
			next_position = current_position - Vec2(1, 0);
		} else if (previous_position != current_position - Point(0, 1) && map::get_flag(current_position - Vec2(0, 1)) == flag) {
			next_position = current_position - Vec2(0, 1);
		}

		return next_position == current_position ? current_position : next_position;
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Calculates the entire path which all enemies use.
	// The path only includes tiles with the 'path' flag, not the 'chest' flag.
	//
	std::vector<Vec2> calculate_path(Vec2 start_position) {
		std::vector<Vec2> path;
		Vec2 previous_position = start_position;
		Vec2 current_position = start_position;
		Vec2 next_position;
		bool has_next_position = true;

		while (has_next_position) {
			next_position = calculate_next_position(previous_position, current_position, map::TileFlags::PATH);
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

	void animate(Timer &timer) {
		for (Enemy &enemy : enemies) {
			enemy.animate(timer);
		}
	}

	void create() {
		Vec2 enemy_start_position = Vec2(0, 1);
		std::vector<Vec2> enemy_path = calculate_path(enemy_start_position);
		enemies.push_back(*new Enemy(enemy_start_position, enemy_path)); //TODO generate enemies automatically with timer

		timer_animate_enemies.init(animate, 100, -1);
		timer_animate_enemies.start();
	}

	void draw() {
		for (Enemy &enemy : enemies) {
			enemy.draw();
		}
	}

	void move() {
		auto itr = enemies.begin();

		while (itr != enemies.end()) {
			if (!itr->move()) {
				enemies.erase(itr++);
			} else {
				itr++;
			}
		}
	}
}
