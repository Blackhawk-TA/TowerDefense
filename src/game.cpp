#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"
#include "handlers/enemies.hpp"
#include "handlers/chests.hpp"
#include "objects/builder.hpp"

using namespace blit;

float ms_start, ms_end;
uint32_t score = 0;
bool build_mode = false;
Builder *builder;

//TODO check if camera is required and how it can be improved
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
	set_screen_mode(ScreenMode::lores);
	screen.sprites = Surface::load(asset_spritesheet);

	map::create();
	map::set_flags(map::TileFlags::PATH, {11, 29, 48, 101});
	map::set_flags(map::TileFlags::BUILDABLE, {102});

	enemies::create();
	chests::create();

	builder = Builder::getInstance();
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

	map::draw(build_mode, &level_line_interrupt_callback);
	chests::draw();
	enemies::draw();

	if (build_mode) {
		builder->draw();
	}

	draw_score();

	ms_end = now();
	draw_fps(ms_start, ms_end);
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
	enemies::move();

	//Handle button inputs
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::B) {
		build_mode = !build_mode;
	}

	if (build_mode) {
		if (buttons & changed & Button::DPAD_UP) {
			builder->move_up();
		} else if (buttons & changed & Button::DPAD_DOWN) {
			builder->move_down();
		} else if (buttons & changed & Button::DPAD_LEFT) {
			builder->move_left();
		} else if (buttons & changed & Button::DPAD_RIGHT) {
			builder->move_right();
		} else if (buttons & changed & Button::X) { //Turn
			builder->turn();
		} else if (buttons & changed & Button::A) { //Build
		}
	}

	last_buttons = buttons;
}
