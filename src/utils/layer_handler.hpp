//
// Created by daniel on 28.02.21.
//

#pragma once
#include "utils.hpp"

using namespace blit;

class LayerHandler {
public:
	enum TileFlags {
		PATH = 1,
		CHEST = 2
	};

	static void generate_map();
	static void draw_map(bool build_mode, std::function<Mat3(uint8_t)> *level_line_interrupt_callback);
	static void set_flags(LayerHandler::TileFlags flag, const std::vector<uint8_t> &tiles);
	static uint8_t get_flag(Point p);
};
