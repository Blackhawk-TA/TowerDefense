//
// Created by daniel on 04.04.21.
//

#pragma once
#include "32blit.hpp"
#include "../objects/chest.hpp"

using namespace blit;

class ChestHandler{
public:
	static ChestHandler *getInstance();
	void draw();
	Chest* get_by_position(Point position);

private:
	static ChestHandler *instance;
	const Point chest_base_position = Point(16, 12);
	std::vector<Chest> chests;

	explicit ChestHandler();
};
