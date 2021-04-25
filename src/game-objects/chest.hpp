//
// Created by daniel on 03.04.21.
//

#pragma once
#include "../utils/utils.hpp"

using namespace blit;

class Chest {
public:
	explicit Chest(Point position);
	void draw();
	void open();
	bool is_open() const;
	Point get_position();

private:
	const uint8_t closed_sprite_id = 36;
	const uint8_t opened_sprite_id = 37;

	uint8_t sprite_id;
	Point position;
};
