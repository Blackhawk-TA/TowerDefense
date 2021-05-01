#include "game.hpp"
#include "assets.hpp"
#include "utils/map.hpp"
#include "utils/ui_overlay.hpp"
#include "handlers/chest_handler.hpp"
#include "handlers/enemy_handler.hpp"
#include "handlers/turret_handler.hpp"
#include "logic-objects/builder.hpp"
#include "logic-objects/credits.hpp"

using namespace blit;

float ms_start, ms_end;
bool build_mode = false;
bool game_running = true;
bool win_game = false;
uint32_t game_time = 0;
uint32_t last_game_time = 0;
Builder *builder;
Credits *credits;
ChestHandler *chest_handler;
EnemyHandler *enemy_handler;
TurretHandler *turret_handler;
Timer *timer_win_condition;

//TODO check if camera is required and how it can be improved
Mat3 camera;
std::function<Mat3(uint8_t)> level_line_interrupt_callback = [](uint8_t y) -> Mat3 {
	return camera;
};

void trigger_win_condition(Timer &timer) {
	win_game = true;
	game_running = false;
}

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
	credits = Credits::getInstance();
	chest_handler = ChestHandler::getInstance();
	enemy_handler = EnemyHandler::getInstance();
	turret_handler = TurretHandler::getInstance();

	timer_win_condition = new Timer();
	timer_win_condition->init(trigger_win_condition, 45000, 1);
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

	if (game_running) {
		game_time = time - last_game_time;
	} else {
		ui_overlay::draw_game_over(win_game);
	}

	ui_overlay::draw_time(game_time);
	ui_overlay::draw_points(credits->get_credits());

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

	//Handle button inputs
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	//Check win condition
	bool has_closed_chest = ChestHandler::getInstance()->get_has_closed_chest();
	bool is_max_spawn_interval = EnemyHandler::getInstance()->get_is_max_spawn_interval();
	if (has_closed_chest && is_max_spawn_interval && !timer_win_condition->is_running()) {
		timer_win_condition->start();
	}

	//Check game over condition
	if (!has_closed_chest) {
		//TODO stop turret timers and enemy animation and delete all handlers and recreate them
		game_running = false;
		if (timer_win_condition->is_running()) {
			timer_win_condition->stop();
		}
	}

	//Update game logic while game is not over
	if (game_running) {
		enemy_handler->move();

		//Handle button presses
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
				//TODO make can_buy_turret method obsolete and show visually when there is not enough money
				if (credits->can_buy_turret() && builder->build()) {
					credits->buy_turret();
				}
			} else if (buttons & changed & Button::B) {
				if (builder->destroy()) {
					credits->refund_turret();
				}
			}
		}
	} else {
		//Reset game
		if (buttons & changed & Button::X) {
			builder->reset();
			chest_handler->reset();
			credits->reset();
			enemy_handler->reset();
			turret_handler->reset();

			build_mode = false;
			win_game = false;
			game_running = true;

			last_game_time = time;
		}
	}

	last_buttons = buttons;
}
