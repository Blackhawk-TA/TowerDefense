//
// Created by daniel on 27.02.21.
//

#pragma once
#include "32blit.hpp"

using namespace blit;

constexpr uint8_t TILE_SIZE = 8;
constexpr uint8_t LEVEL_WIDTH = 32;
constexpr uint8_t LEVEL_HEIGHT = 32;
constexpr uint32_t LEVEL_SIZE = LEVEL_WIDTH * LEVEL_HEIGHT;

enum TurretFacingDirection {
	DOWN = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3
};

Vec2 screen_to_world(const Vec2 &p);

Point world_to_screen(const Point &p);
Vec2 world_to_screen(const float &x, const float &y);

Point get_screen_tiles();
bool sprite_in_screen(Point position, Point &camera_position_world);
bool is_pico_console();
Point get_camera_offset();
