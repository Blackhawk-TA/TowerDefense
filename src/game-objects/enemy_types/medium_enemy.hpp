//
// Created by daniel on 14.05.21.
//

#pragma once
#include "../enemy.hpp"

class MediumEnemy: public Enemy {
public:
	explicit MediumEnemy(Vec2 start_position, std::vector<Vec2> &path);
	EnemyType get_type() override;
};
