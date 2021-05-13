//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include "assets.hpp"
#include "map.hpp"

using namespace blit;

namespace map {
	constexpr uint8_t layer_count = 3;
	constexpr uint8_t flag_count = 3;

	std::array<std::vector<uint8_t>, flag_count> flags;
	uint8_t *layer_data[layer_count];
	TileMap *layers[layer_count];

	void create() {
		TMX *tmx = (TMX *) asset_map;

		if (tmx->width > LEVEL_WIDTH) return;
		if (tmx->height > LEVEL_HEIGHT) return;

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

	void draw(bool &build_mode, std::function<Mat3(uint8_t)> *level_line_interrupt_callback) {
		uint8_t drawing_layers = layer_count;
		if (!build_mode) {
			drawing_layers--;
		}

		for (auto i = 0u; i < drawing_layers; i++) {
			layers[i]->draw(&screen, Rect(0, 0, screen.bounds.w, screen.bounds.h), *level_line_interrupt_callback);
		}
	}

	///////////////////////////////////////////////////////////////////////////
	//
	// Gets the flag of the given sprite on its highest layer, ignoring all underlying flags
	//
	uint8_t get_flag(Point p) {
		uint8_t i = layer_count;
		uint8_t j, k;
		uint8_t tile_id;
		uint8_t flag_enum_id = 0;
		bool flag_found = false;

		while (!flag_found && i > 0) {
			i--;
			j = 0;
			tile_id = layers[i]->tile_at(p);

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
