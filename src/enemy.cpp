//
// Created by daniel on 29.03.21.
//

#include "enemy.hpp"

using namespace blit;

Enemy::Enemy() {
	health = 100;
	position = Point(0, 0);
};

void Enemy::draw() {
	screen.sprite(Rect(tile.x, tile.y, size.x, size.y), position);
}

void Enemy::move(Point next_tile) {
}