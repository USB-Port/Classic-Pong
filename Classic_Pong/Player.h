/*
*	Author: USB-Port
*	File:   player.h
*	Date:   January 3rd 2017
*
*	This is the header file to the player class.
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "allegro5\allegro.h"

class Player
{
public:
	Player();
	~Player();

	float get_pos_x();
	float get_pos_y();

	void set_pos_x(float x);
	void set_pos_y(float y);

	int get_image_height();
	int get_image_width();

	int get_score();
	void set_score(int score);

	void draw_paddle();


private:

	ALLEGRO_BITMAP *paddle_picture;

	int image_height;
	int image_width;

	float pos_x;
	float pos_y;

	int score;

};
#endif