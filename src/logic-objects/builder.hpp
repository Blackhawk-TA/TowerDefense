//
// Created by daniel on 07.04.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Builder {
public:
	static Builder *getInstance();
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	void turn();
	bool build();
	bool destroy();
	void reset();

private:
	const uint8_t SPRITE_TILE_DENY_ID = 103;
	const uint8_t SPRITE_TILE_ALLOW_ID = 104;

	static Builder *instance;
	Point screen_tiles;
	Point position;
	Point turn_direction;
	uint8_t turn_index;
	uint8_t sprite_tile_id;
	std::array<uint8_t, 4> sprite_arrow_ids{};
	std::vector<std::vector<bool>> occupied_tiles{};

	explicit Builder();
	void move(Point movement);
	void update_tile_sprite();
	bool is_building_ground();
	bool can_build();
	bool is_occupied(Point tile);
	void set_occupied(Point tile, bool value);
	Point calculate_turret_position();
};
