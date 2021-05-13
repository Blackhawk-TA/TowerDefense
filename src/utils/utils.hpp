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
constexpr Point SCREEN_TILES = Point(19, 14);

enum TurretFacingDirection {
	DOWN = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3
};

Vec2 screen_to_world(const Vec2 &p);

Point world_to_screen(const Point &p);
Vec2 world_to_screen(const float &x, const float &y);
