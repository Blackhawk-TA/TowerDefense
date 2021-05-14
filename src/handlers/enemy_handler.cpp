//
// Created by daniel on 03.04.21.
//

#include "enemy_handler.hpp"
#include <random>

using namespace blit;

EnemyHandler *EnemyHandler::instance = nullptr;
Timer *EnemyHandler::timer_spawn_enemies = nullptr;
uint16_t EnemyHandler::spawn_delay = DEFAULT_SPAWN_DELAY;
uint8_t EnemyHandler::spawn_counter = 0;
std::vector<Vec2> EnemyHandler::enemy_path = {};
bool EnemyHandler::is_min_spawn_interval = false;

EnemyHandler *EnemyHandler::getInstance() {
	if (instance == nullptr) {
		instance = new EnemyHandler();
	}
	return instance;
}

Timer *EnemyHandler::get_timer_spawn_enemies() {
	if (timer_spawn_enemies == nullptr) {
		timer_spawn_enemies = new Timer();
	}
	return timer_spawn_enemies;
}

EnemyHandler::EnemyHandler() {
	enemy_path = calculate_path(ENEMY_START_POSITION);

	get_timer_spawn_enemies()->init(spawn, INITIAL_SPAWN_DELAY, 1);
	get_timer_spawn_enemies()->start();

	timer_animate_enemies.init(animate, 100, -1);
	timer_animate_enemies.start();
}

bool EnemyHandler::get_is_max_spawn_interval() {
	return is_min_spawn_interval;
}

std::list<Enemy> &EnemyHandler::get_enemies() {
	return enemies;
}

void EnemyHandler::spawn(Timer &timer) {
	//Generate random number for enemy spawn type
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0,100);
	int rand_enemy = dist(mt);

	if (rand_enemy < 80) {
		EnemyHandler::getInstance()->enemies.push_back(EasyEnemy(ENEMY_START_POSITION, enemy_path));
	} else if (rand_enemy < 95){
		EnemyHandler::getInstance()->enemies.push_back(MediumEnemy(ENEMY_START_POSITION, enemy_path));
	} else {
		EnemyHandler::getInstance()->enemies.push_back(HardEnemy(ENEMY_START_POSITION, enemy_path));
	}

	//Decrease spawn interval
	if (spawn_counter == 2 && spawn_delay >= MIN_SPAWN_DELAY) {
		spawn_counter = 0;
		spawn_delay = std::floor(spawn_delay * 0.85);
	}

	//Check if spawn interval is at minimum
	if (!is_min_spawn_interval && spawn_delay < MIN_SPAWN_DELAY) {
		is_min_spawn_interval = true;
	}

	//Randomly spawn additional enemy with a 15% chance
	if (dist(mt) < 15) {
		EnemyHandler::get_timer_spawn_enemies()->duration = MIN_SPAWN_DELAY;
	} else {
		EnemyHandler::get_timer_spawn_enemies()->duration = spawn_delay;
	}

	EnemyHandler::get_timer_spawn_enemies()->start();
	spawn_counter++;
}

void EnemyHandler::animate(Timer &timer) {
	for (Enemy &enemy : EnemyHandler::getInstance()->enemies) {
		enemy.animate(timer);
	}
}

void EnemyHandler::draw() {
	for (Enemy &enemy : enemies) {
		enemy.draw();
	}
}

void EnemyHandler::move() {
	auto itr = enemies.begin();

	while (itr != enemies.end()) {
		if (!itr->move()) {
			enemies.erase(itr++);
		} else {
			itr++;
		}
	}
}

void EnemyHandler::reset() {
	enemies.clear();
	spawn_delay = DEFAULT_SPAWN_DELAY;
	spawn_counter = 0;
	is_min_spawn_interval = false;

	//Restart timer with initial spawn delay
	get_timer_spawn_enemies()->stop();
	get_timer_spawn_enemies()->duration = INITIAL_SPAWN_DELAY;
	get_timer_spawn_enemies()->start();
}

///////////////////////////////////////////////////////////////////////////
//
// Calculates the next position based on current_position.
// TileFlags are used to determine if the enemy can move to a tile.
//
Vec2 EnemyHandler::calculate_next_position(Vec2 previous_position, Vec2 current_position, map::TileFlags flag) {
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
std::vector<Vec2> EnemyHandler::calculate_path(Vec2 start_position) {
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
