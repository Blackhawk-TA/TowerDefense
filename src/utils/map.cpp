//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

namespace map {
	constexpr uint8_t LAYER_COUNT = 3;

	std::array<std::vector<uint8_t>, TileFlags::COUNTER> flags;
	uint8_t *layer_data[LAYER_COUNT];
	TileMap *layers[LAYER_COUNT];
	Point camera_position_world;
	uint8_t empty_tile;

	void create() {
		TMX *tmx = (TMX *) asset_map;

		if (tmx->width > LEVEL_WIDTH) return;
		if (tmx->height > LEVEL_HEIGHT) return;

		empty_tile = tmx->empty_tile;

		//Set camera position for Pico
		camera_position_world = get_camera_offset();

		for (auto i = 0u; i < tmx->layers; i++) {
			layer_data[i] = (uint8_t *) malloc(LEVEL_SIZE);
			layers[i] = new TileMap((uint8_t *) layer_data[i], nullptr, Size(LEVEL_WIDTH, LEVEL_HEIGHT), screen.sprites);

			// Load the level data from the map memory
			memset(layer_data[i], 0, LEVEL_SIZE);

			for (auto x = 0u; x < tmx->width; x++) {
				for (auto y = 0u; y < tmx->height; y++) {
					auto src = y * tmx->width + x;
					auto dst = y * LEVEL_WIDTH + x;
					layer_data[i][dst] = tmx->data[src + i * LEVEL_SIZE];
				}
			}
		}
	}

	void draw(bool &build_mode) {
		uint8_t drawing_layers = LAYER_COUNT;
		if (!build_mode) {
			drawing_layers--;
		}

		uint8_t x_position, y_position;
		uint8_t sprite_id;
		for (auto z = 0u; z < drawing_layers; z++) {
			for (auto x = 0; x < LEVEL_WIDTH; x++) {
				for (auto y = 0; y < LEVEL_HEIGHT; y++) {
					x_position = x - camera_position_world.x;
					y_position = y - camera_position_world.y;

					if (sprite_in_screen(Point(x, y), camera_position_world)) {
						sprite_id = layer_data[z][y * LEVEL_WIDTH + x];

						if (sprite_id != empty_tile) {
							screen.sprite(sprite_id, Point(x_position, y_position) * TILE_SIZE);
						}
					}
				}
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
	//
	uint8_t get_flag(Point p) {
		uint8_t i = LAYER_COUNT;
		uint8_t j, k;
		uint8_t tile_id;
		uint8_t flag_enum_id = 0;
		bool flag_found = false;

		while (!flag_found && i > 0) {
			i--;
			j = 0;
			tile_id = layers[i]->tile_at(p + get_camera_offset());

			while (!flag_found && j < flags.size() - 1) {
				j++;
				k = 0;
				while (!flag_found && k < flags[j].size()) {
					if (tile_id == flags[j].at(k)) {
						flag_enum_id = j;
						flag_found = true;
					}
					k++;
				}
			}
		}

		return flag_enum_id;
	}

	void set_flags(TileFlags flag, const std::vector<uint8_t> &tiles) {
		flags[flag] = tiles;
	}
}
