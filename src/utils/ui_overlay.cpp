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
		std::string fms = std::to_string((int) (1 / ((ms_end - ms_start) / 1000)));
		screen.text(fms, minimal_font, Rect(3, screen.bounds.h - 9, 10, 16));

		int block_size = 4;
		for (uint32_t i = 0; i < (ms_end - ms_start); i++) {
			screen.pen = Pen((int) i * 5, 255 - ((int) i * 5), 0);
			screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
		}
	}

	const size_t required_space = 6;
	time_t time_sec;

	void draw_time(uint32_t time) {
		screen.pen = Pen(255, 255, 255, 200);
		time_sec = time / 1000;
		std::string time_string(required_space, ' ');
		std::strftime(&time_string[0], required_space, "%M:%S", std::localtime(&time_sec));

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
}
