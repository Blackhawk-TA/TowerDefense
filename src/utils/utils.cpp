//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / TILE_SIZE, p.y / TILE_SIZE);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * TILE_SIZE, p.y * TILE_SIZE);
}

Vec2 world_to_screen(const float &x, const float &y) {
	return Vec2(std::ceil(x * TILE_SIZE), std::ceil(y * TILE_SIZE));
}

/**
 * Get amount of tiles that can be displayed on the screen's x and y-axis
 * @return The amount of tiles that can be displayed at the screen stored as Point
 */
Point get_screen_tiles() {
	return Point(screen.bounds.w / TILE_SIZE, screen.bounds.h / TILE_SIZE);
}

/**
 * Check if a sprite is within the screen bounds.
 * @param position The position of the sprite
 * @param camera_position_world The camera offset of the sprite in world coordinates
 * @return True, if the sprite is within the screen bounds, else false.
 */
bool sprite_in_screen(Point position, Point &camera_position_world) {
	Point screen_tiles = get_screen_tiles();

	return camera_position_world.x <= position.x &&
	       camera_position_world.y <= position.y &&
	       screen_tiles.x + camera_position_world.x - position.x > 0 &&
	       screen_tiles.y + camera_position_world.y - position.y > 0;
}

/**
 * Check if the currently used console is a PicoSystem by checking its width
 * @return True, if the console is a PicoSystem, else false.
 */
bool is_pico_console() {
	return screen.bounds.w == 120;
}

/**
 * Gets the camera offset required for the squared display of the PicoSystem
 * @return The camera offset
 */
Point get_camera_offset() {
	return is_pico_console() ? Point(2, 0) : Point(0, 0);
}
