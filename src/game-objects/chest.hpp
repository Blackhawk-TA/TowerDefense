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
	void close();
	bool is_open() const;
	Point get_position();

private:
	const uint8_t CLOSED_SPRITE_ID = 36;
	const uint8_t OPENED_SPRITE_ID = 37;

	uint8_t sprite_id;
	Point position;
};
