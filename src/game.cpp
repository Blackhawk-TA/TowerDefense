#include "game.hpp"
#include "assets.hpp"
#include "utils/layer_handler.hpp"

using namespace blit;

float ms_start, ms_end;
Mat3 camera;
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
	set_screen_mode(ScreenMode::lores); // Maybe use different screen mode
	screen.sprites = Surface::load(asset_spritesheet);

	LayerHandler::generate_map();
}

void draw_fps() {
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(1, 120 - 10, 20, 9));
	screen.pen = Pen(255, 255, 255, 200);
	int fps = (int)(1 / ((ms_end - ms_start)/1000));
	std::string fms = std::to_string(std::max(fps, 999));
	screen.text(fms, minimal_font, Rect(3, 120 - 9, 10, 16));

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

	ms_end = now();
//	draw_fps();
}

void update_camera(uint32_t time) {
	camera = Mat3::identity();
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	update_camera(time);
}