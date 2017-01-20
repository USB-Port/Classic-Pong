/*
*	Author: USB-Port
*	File:   ball.cpp
*	Date:   January 3rd 2017
*
*	This is the ball class file
*/
#include <iostream>
#include "Ball.h"

using namespace std;

Ball::Ball(int x, int y)
{
	try {
		ball_picture = al_load_bitmap("./ball_picture.png");
		ping_sound = al_load_sample("./ping_sound.ogg");
	}
	catch (exception e) {
		cout << "Failed to load ./ball_picture.png";
		cout << "Failed to load ./ping_sound.ogg";
	}

	al_convert_mask_to_alpha(ball_picture, al_map_rgb(255, 0, 255));

	image_height = al_get_bitmap_height(ball_picture);
	image_width = al_get_bitmap_width(ball_picture);

	pos_x = x;
	pos_y = y;
	bouncer_x = 1;
	bouncer_y = 1;
	speed = 2;
}

Ball::~Ball()
{
	if (!ball_picture) {
		al_destroy_bitmap(ball_picture);
	}
}

float Ball::get_pos_x() {
	return pos_x;
}
float Ball::get_pos_y() {
	return pos_y;
}

void Ball::set_pos_x(float x) {
	pos_x = x;
}
void Ball::set_pos_y(float y) {
	pos_y = y;
}

int Ball::get_image_height() {
	return image_height;
}
int Ball::get_image_width() {
	return image_width;
}

void Ball::draw_ball() {
	al_draw_bitmap(ball_picture, pos_x, pos_y, 0);
}

void Ball::play_sound() {
	al_play_sample(ping_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

}

int Ball::get_speed() {
	return speed;
}
void Ball::set_speed(int speed) {
	this->speed = speed;
}

void Ball::increment_speed() {
	speed++;
}

int Ball::get_bouncer_x() {
	return bouncer_x;
}
int Ball::get_bouncer_y() {
	return bouncer_y;
}

void Ball::flip_bouncer_x() {
	bouncer_x *= -1;
}
void Ball::flip_bouncer_y() {
	bouncer_y *= -1;
}