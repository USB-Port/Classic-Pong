/*
*	Author: USB-Port
*	File:   ball.h
*	Date:   January 3rd 2017
*
*	This is the header file to the ball class.
*/

#pragma once
#ifndef BALL_H
#define BALL_H
#include "allegro5\allegro.h"
#include <allegro5/allegro_audio.h>

class Ball {

public:

	Ball(int x, int y);
	~Ball();

	float get_pos_x();
	float get_pos_y();

	void set_pos_x(float x);
	void set_pos_y(float y);

	int get_image_height();
	int get_image_width();

	void draw_ball();

	void play_sound();


private:

	ALLEGRO_BITMAP *ball_picture;
	ALLEGRO_SAMPLE *ping_sound;

	int image_height;
	int image_width;

	float pos_x;
	float pos_y;


};
#endif