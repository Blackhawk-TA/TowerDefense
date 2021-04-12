#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"
#include "utils/ui_overlay.hpp"
#include "handlers/chest_handler.hpp"
#include "handlers/enemy_handler.hpp"
#include "handlers/turret_handler.hpp"
#include "objects/builder.hpp"

using namespace blit;

float ms_start, ms_end;
uint32_t points = 0;
bool build_mode = false;
Builder *builder;
ChestHandler *chest_handler;
EnemyHandler *enemy_handler;
TurretHandler *turret_handler;

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

	builder = Builder::getInstance();
	chest_handler = ChestHandler::getInstance();
	enemy_handler = EnemyHandler::getInstance();
	turret_handler = TurretHandler::getInstance();
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

	if (build_mode) {
		builder->draw();
	}

	chest_handler->draw();
	enemy_handler->draw();
	turret_handler->draw();

	ui_overlay::draw_time(time);
	ui_overlay::draw_points(points);

	ms_end = now();
	ui_overlay::draw_fps(ms_start, ms_end);
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
	enemy_handler->move();

	//Handle button inputs
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::X) {
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
		} else if (buttons & changed & Button::Y) {
			builder->turn();
		} else if (buttons & changed & Button::A) {
			if (builder->build()) {
				//TODO pay turret with points
			}
		} else if (buttons & changed & Button::B) {
			if (builder->destroy()) {
				//TODO refund points
			}
		}
	}

	last_buttons = buttons;
}
