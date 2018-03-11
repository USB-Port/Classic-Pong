/*
*	Author: USB-Port
*	File:   player.cpp
*	Date:   January 3rd 2017
*
*	This is the player class file.
*/
#include <iostream>
#include "Player.h"
#include "allegro5\allegro_native_dialog.h"

using namespace std;

//Constructor
Player::Player()
{
	try {
		paddle_picture = al_load_bitmap("./player_one.png");
	}
	catch (exception e)
	{
		cout << "Failed to load ./player_one.png";
		
	}
	al_convert_mask_to_alpha(paddle_picture, al_map_rgb(255, 0, 255));

	image_height = al_get_bitmap_height(paddle_picture);
	image_width = al_get_bitmap_width(paddle_picture);

	pos_x = 100;
	pos_y = 0;

	score = 0;
}


Player::~Player()
{
	if (!paddle_picture) {
		al_destroy_bitmap(paddle_picture);
	}
}

void Player::draw_paddle(void) {
	al_draw_bitmap(paddle_picture, pos_x, pos_y, 0);
}

float Player::get_pos_x() {
	return pos_x;
}
float Player::get_pos_y() {
	return pos_y;
}

void Player::set_pos_x(float x) {
	pos_x = x;
}
void Player::set_pos_y(float y) {
	pos_y = y;
}
int Player::get_image_height() {
	return image_height;
}
int Player::get_image_width() {
	return image_width;
}
int Player::get_score() {
	return score;
}
void Player::set_score(int score) {
	this->score = score;
}
