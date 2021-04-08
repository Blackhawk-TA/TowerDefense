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

private:
	static Builder *instance;
	explicit Builder();
	Point position;
	Point turn_direction;
	uint8_t sprite_deny_id;
	uint8_t sprite_allow_id;
	uint8_t sprite_id;
	bool build_vertical;

	void move(Point direction);
	void update_sprite();
};
