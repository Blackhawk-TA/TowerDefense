//
// Created by Daniel Peters on 12.04.21.
//

#include <ctime>
#include "ui_overlay.hpp"

using namespace blit;

namespace ui_overlay {
	void draw_fps(float &ms_start, float &ms_end) {
		screen.alpha = 255;
		screen.pen = Pen(255, 255, 255, 100);
		screen.rectangle(Rect(1, screen.bounds.h - 10, 20, 9));
		screen.pen = Pen(255, 255, 255, 200);
		std::string fms = std::to_string(static_cast<int>(1 / ((ms_end - ms_start) / 1000)));
		screen.text(fms, minimal_font, Rect(3, screen.bounds.h - 9, 10, 16));

		int block_size = 4;
		for (int i = 0; i < static_cast<int>(ms_end - ms_start); i++) {
			screen.pen = Pen(i * 5, 255 - (i * 5), 0);
			screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
		}
	}

	const size_t REQUIRED_SPACE = 6;
	time_t time_sec;

	void draw_time(uint32_t time) {
		screen.pen = Pen(255, 255, 255, 200);
		time_sec = time / 1000;
		std::string time_string(REQUIRED_SPACE, ' ');
		std::strftime(&time_string[0], REQUIRED_SPACE, "%M:%S", std::localtime(&time_sec));

		screen.text(time_string,
			minimal_font,
			Rect(1, 1, 10, 16),
			true,
			TextAlign::top_left
		);
	}

	void draw_points(uint32_t points) {
		screen.pen = Pen(255, 255, 255, 200);
		screen.text(std::to_string(points),
			minimal_font,
			Rect(screen.bounds.w - 10, 1, 10, 16),
			true,
			TextAlign::top_right
		);
	}

	int box_width = 80;
	int box_height = 30;
	std::string game_over_text;

	void draw_game_over(bool win_game) {
		screen.pen = Pen(255, 255, 255, 200);
		screen.rectangle(Rect(screen.bounds.w / 2 - box_width / 2, screen.bounds.h / 2 - box_height / 2, box_width, box_height));

		if (win_game) {
			game_over_text = "You Win!\nPress X";
		} else {
			game_over_text = "Game Over\nPress X";
		}
		screen.pen = Pen(0, 0, 0, 200);
		screen.text(game_over_text,
			outline_font,
			Point(screen.bounds.w / 2, screen.bounds.h / 2),
			false,
			TextAlign::center_center
		);
	}
}
