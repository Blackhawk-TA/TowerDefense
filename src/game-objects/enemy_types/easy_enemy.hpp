//
// Created by daniel on 14.05.21.
//

#pragma once
#include "../enemy.hpp"

class EasyEnemy: public Enemy {
public:
	explicit EasyEnemy(Vec2 start_position, std::vector<Vec2> &path);
};
