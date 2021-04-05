//
// Created by daniel on 04.04.21.
//

#include "chests.hpp"
#include "../objects/chest.hpp"

using namespace blit;

namespace chests {
	constexpr Point chest_base_position = Point(16, 12);
	std::vector<Chest> chests;

	void create() {
		for (auto i = 0u; i < 3; i++) {
			chests.push_back(*new Chest(Point(chest_base_position.x + i, chest_base_position.y)));
		}
	}

	void draw() {
		for (Chest &chest : chests) {
			chest.draw();
		}
	}

	Chest* get_by_position(Point position) {
		uint8_t i = 0;
		Chest *chest = nullptr;

		while (!chest && i < chests.size()) {
			if (chests.at(i).get_position() == position) {
				chest = &chests.at(i);
			}
			i++;
		}

		return chest;
	}
}
