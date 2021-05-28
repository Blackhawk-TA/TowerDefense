//
// Created by daniel on 03.04.21.
//

#pragma once
#include <list>
#include "../game-objects/enemies/medium_enemy.hpp"
#include "../game-objects/enemies/hard_enemy.hpp"
#include "../utils/map.hpp"

class EnemyHandler {
public:
	static EnemyHandler *getInstance();
	static bool get_is_max_spawn_interval();
	static uint16_t get_initial_spawn_delay();
	void draw();
	void move();
	void reset();
	std::list<Enemy> &get_enemies();

private:
	static constexpr uint8_t DEFAULT_EASY_ENEMY_SPAWN_RATE = 80;
	static constexpr uint8_t DEFAULT_MEDIUM_ENEMY_SPAWN_RATE = 15;
	static constexpr uint8_t DEFAULT_HARD_ENEMY_SPAWN_RATE = 5;
	static constexpr uint16_t DEFAULT_SPAWN_DELAY = 10000; //Default delay between two enemies
	static const uint16_t INITIAL_SPAWN_DELAY = 10000; //Delay for the first enemy
	static const uint16_t MIN_SPAWN_DELAY = 500; //Delay for the first enemy
	static const uint8_t ANIMATION_INTERVAL = 100;
	static constexpr Vec2 ENEMY_START_POSITION = Vec2(-1, 1);

	static EnemyHandler *instance;
	static std::vector<Vec2> enemy_path;
	static uint16_t spawn_delay;
	static uint8_t spawn_counter;
	static Timer *timer_spawn_enemies;
	static bool is_min_spawn_interval;

	//Enemy type spawn rates in percent
	static uint8_t easy_enemy_spawn_rate;
	static uint8_t medium_enemy_spawn_rate;
	static uint8_t hard_enemy_spawn_rate;

	Timer timer_animate_enemies;
	std::list<Enemy> enemies;

	explicit EnemyHandler();
	static Timer *get_timer_spawn_enemies();
	static Vec2 calculate_next_position(Vec2 previous_position, Vec2 current_position, map::TileFlags flag);
	static std::vector<Vec2> calculate_path(Vec2 start_position);
	static void spawn(Timer &timer);
	static void animate(Timer &timer);
};
