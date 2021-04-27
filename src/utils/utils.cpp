//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / tile_size, p.y / tile_size);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * tile_size, p.y * tile_size);
}

Vec2 world_to_screen(const float &x, const float &y) {
	return Vec2(std::ceil(x * tile_size), std::ceil(y * tile_size));
}
