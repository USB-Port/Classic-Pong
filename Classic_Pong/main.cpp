#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "Ball.h"
#include "Player.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define PADDLE_SPEED 6
#define PLAYER_ONE 0
#define PLAYER_TWO 1

using namespace std;

const float FPS = 60;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int setup() {
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to image addon!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	if (!al_install_audio()) {
		fprintf(stderr, "failed to install audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize acodec addon!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve sample!\n");
		return -1;
	}

	if (!al_init_font_addon()) {
		fprintf(stderr, "failed to initialize font addon!\n");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize true text format addon!\n");
		return -1;
	}

	return 0;
}


int main() {


	ALLEGRO_DISPLAY			 *display = NULL;
	ALLEGRO_DISPLAY_MODE      disp_data;
	ALLEGRO_TIMER			 *timer = NULL;
	ALLEGRO_EVENT_QUEUE	     *event_queue = NULL;

	bool redraw = true;
	bool exit   = false;

	bool key[4] = { false, false, false, false };

	if (setup()) {
		fprintf(stderr, "There was an error in the setup process");
		return -1;
	}
	
	timer = al_create_timer(1.0 / FPS);

	if (!timer) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	event_queue = al_create_event_queue();

	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a event_queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_WINDOWED);					//WINDOWED or FULLSCREEN
																//display = al_create_display(disp_data.width, disp_data.height);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	int hits = 0;
	int player_one_score = 0;
	int player_two_score = 0;
	int bouncer_x = -1;
	int bouncer_y = -1;
	int ball_speed = 2;

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 255, 0));
	al_flip_display();

	al_start_timer(timer);

	Ball ball;
	Player player[2];
	player[1].set_pos_x(SCREEN_WIDTH - 20);
	
	//Start of the game loop
	while (!exit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			// updating game logic goes here
			if (ball.get_pos_x() < 0 || ball.get_pos_x() > SCREEN_WIDTH - ball.get_image_width()) {
				bouncer_x = bouncer_x*-1;
				ball.play_sound();
			}

			if (ball.get_pos_x() < 0) {
				player_two_score++;
			}

			if (ball.get_pos_x() > SCREEN_WIDTH - ball.get_image_width()) {
				player_one_score++;
			}


			if (ball.get_pos_y() < 0 || ball.get_pos_y() > SCREEN_HEIGHT - ball.get_image_height()) {
				bouncer_y = bouncer_y*-1;
				ball.play_sound();
			}

			if (ball.get_pos_x() >= player[0].get_pos_x() && ball.get_pos_x() < player[0].get_pos_x() + player[0].get_image_width() &&
				ball.get_pos_y() >= player[0].get_pos_y() && ball.get_pos_y() < player[0].get_pos_y() + player[0].get_image_height()) {
				bouncer_x = bouncer_x*-1;
				ball.play_sound();
				hits++;
			}

			if (ball.get_pos_x() >= player[1].get_pos_x() && ball.get_pos_x() < player[1].get_pos_x() + player[1].get_image_width() &&
				ball.get_pos_y() >= player[1].get_pos_y() && ball.get_pos_y() < player[1].get_pos_y() + player[1].get_image_height()) {
				bouncer_x = bouncer_x*-1;
				ball.play_sound();
				hits++;
			}



			ball.set_pos_x(ball.get_pos_x() + ball_speed*bouncer_x);
			ball.set_pos_y(ball.get_pos_y() + ball_speed*bouncer_y);

			if (hits > 3) {
				hits = 0;
				ball_speed++;
			}


			if (ball.get_pos_y() > player[1].get_pos_y()) {
				player[1].set_pos_y(player[1].get_pos_y() + PADDLE_SPEED);
			}


			if (ball.get_pos_y() < player[1].get_pos_y()) {
				player[1].set_pos_y(player[1].get_pos_y() - PADDLE_SPEED);
			}

			///////////////THHINGS TO DO WHEN BUTTON IS PRESSED////////////////////
			if (key[KEY_UP]) {
				player[0].set_pos_y(player[0].get_pos_y() - PADDLE_SPEED);
				if (player[0].get_pos_y() < 0) {
					player[0].set_pos_y(0);
				}
			}

			if (key[KEY_DOWN]) {
				player[0].set_pos_y(player[0].get_pos_y() + PADDLE_SPEED);

				if (player[0].get_pos_y() + player[0].get_image_height() > SCREEN_HEIGHT) {
					player[0].set_pos_y(SCREEN_HEIGHT - player[0].get_image_height());
				}
			}

			if (key[KEY_LEFT]) {

			}

			if (key[KEY_RIGHT]) {

			}

			redraw = true;
		}//timer if statement

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				exit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//////////////DRAW STUFF HERE//////////////////////

			player[0].draw_paddle();
			player[1].draw_paddle();
			ball.draw_ball();

			al_flip_display();

		} // end of updating game logic
	} // game loop

}

