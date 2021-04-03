#include "game.hpp"
#include "assets.hpp"
#include "utils/layer_handler.hpp"
#include "utils/enemy_handler.hpp"
#include "objects/enemy.hpp"
#include "objects/chest.hpp"

using namespace blit;

constexpr Point chest_base_position = Point(16, 12);
std::vector<Enemy> enemies;
std::vector<Chest> chests;
float ms_start, ms_end;
uint32_t score = 0;

Mat3 camera; //TODO check if camera is required and how it can be improved
std::function<Mat3(uint8_t)> level_line_interrupt_callback = [](uint8_t y) -> Mat3 {
	return camera;
};


///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	set_screen_mode(ScreenMode::lores);
	screen.sprites = Surface::load(asset_spritesheet);

	LayerHandler::generate_map();
	LayerHandler::set_flags(LayerHandler::PATH, {48});
	LayerHandler::set_flags(LayerHandler::CHEST, {101});

	//Create chests
	for(auto i = 0u; i < 3; i++) {
		chests.push_back(*new Chest(Point(chest_base_position.x + i, chest_base_position.y)));
	}

	std::vector<Point> enemy_path = EnemyHandler::calculate_path(Point(0, 0));

	enemies.push_back(*new Enemy(Point(0, 0), enemy_path)); //TODO generate enemies automatically
}

void draw_score() {
	screen.pen = Pen(255, 255, 255, 200);
	screen.text(std::to_string(score),
		minimal_font,
		Rect(screen.bounds.w - 10, 1, 10, 16),
		true,
		TextAlign::top_right
	);
}

void draw_fps() {
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(1, screen.bounds.h - 10, 20, 9));
	screen.pen = Pen(255, 255, 255, 200);
	std::string fms = std::to_string((int)(1/((ms_end - ms_start)/1000)));
	screen.text(fms, minimal_font, Rect(3, screen.bounds.h - 9, 10, 16));

	int block_size = 4;
	for (uint32_t i = 0; i < (ms_end - ms_start); i++) {
		screen.pen = Pen((int)i * 5, 255 - ((int)i * 5), 0);
		screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
	}
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
	ms_start = now();
	screen.clear();

	LayerHandler::draw_map(&level_line_interrupt_callback);

	for (Enemy &enemy : enemies) {
		enemy.draw();
	}
	for (Chest &chest : chests) {
		chest.draw();
	}

	draw_score();

	ms_end = now();
	draw_fps();
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	camera = Mat3::identity();
}