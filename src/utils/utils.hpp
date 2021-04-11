//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

constexpr uint8_t tile_size = 8;
constexpr uint8_t level_width = 32;
constexpr uint8_t level_height = 32;
constexpr uint32_t level_size = level_width * level_height;
constexpr Point screen_tiles = Point(19, 14);

enum TurretFacingDirection {
	DOWN = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3
};

Point screen_to_world(const Point &p);
Vec2 screen_to_world(const Vec2 &p);

Point world_to_screen(const Point &p);
Vec2 world_to_screen(const Vec2 &p);
Vec2 world_to_screen(const float &x, const float &y);

void draw_fps(float &ms_start, float &ms_end);
