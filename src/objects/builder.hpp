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

private:
	static Builder *instance;
	Point position;
	Point turn_direction;
	uint8_t turn_index;
	uint8_t sprite_deny_id;
	uint8_t sprite_allow_id;
	uint8_t sprite_id;
	std::array<uint8_t, 4> sprite_array_ids{};
	std::array<bool, screen_tiles.x * screen_tiles.y> occupied_tiles{};

	explicit Builder();
	void move(Point movement);
	void update_sprite();
};
