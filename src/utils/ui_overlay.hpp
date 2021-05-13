//
// Created by Daniel Peters on 12.04.21.
//

#pragma once
#include "32blit.hpp"

namespace ui_overlay {
	void draw_time(uint32_t time);
	void draw_game_info(std::string info_text, uint32_t time);
	void draw_points(uint32_t points);
	void draw_fps(float &ms_start, float &ms_end);
	void draw_game_over(bool win_game);
}
