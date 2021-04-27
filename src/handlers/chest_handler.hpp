//
// Created by daniel on 04.04.21.
//

#pragma once
#include "32blit.hpp"
#include "../game-objects/chest.hpp"

using namespace blit;

class ChestHandler{
public:
	static ChestHandler *getInstance();
	bool get_has_closed_chest() const;
	void draw();
	bool open_by_position(Point position);
	void reset();

private:
	static ChestHandler *instance;
	const Point chest_base_position = Point(16, 12);
	bool has_closed_chest;
	std::vector<Chest> chests;

	explicit ChestHandler();
	Chest* get_by_position(Point position);
	void check_closed_chests();
};
