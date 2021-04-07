//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Point screen_to_world(const Point &p) {
	return Point(p.x / tile_size, p.y / tile_size);
}

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / tile_size, p.y / tile_size);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * tile_size, p.y * tile_size);
}

Vec2 world_to_screen(const Vec2 &p) {
	return Vec2(std::ceil(p.x * tile_size), std::ceil(p.y * tile_size));
}

Vec2 world_to_screen(const float &x, const float &y) {
	return Vec2(std::ceil(x * tile_size), std::ceil(y * tile_size));
}

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

