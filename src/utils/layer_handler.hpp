//
// Created by daniel on 28.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

class LayerHandler {

public:
	enum TileFlags {
		WALL = 1,
	};

	static void draw_map(std::function<Mat3(uint8_t)> *level_line_interrupt_callback);
	static void generate_map();
	static void set_flags(LayerHandler::TileFlags flag, const std::vector<uint8_t> &tiles);
	static uint8_t get_flag(Point p);
};
