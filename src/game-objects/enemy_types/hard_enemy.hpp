//
// Created by daniel on 14.05.21.
//

#pragma once
#include "../enemy.hpp"

class HardEnemy: public Enemy {
public:
	explicit HardEnemy(Vec2 start_position, std::vector<Vec2> &path);
	~HardEnemy() override = default;
	EnemyType get_type() override;
};
