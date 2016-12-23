#include "Ball.h"

Ball::Ball()
{
	ball_picture = al_load_bitmap("./ball_picture.png");
	ping_sound = al_load_sample("./ping_sound.ogg");
	al_convert_mask_to_alpha(ball_picture, al_map_rgb(255, 0, 255));

	image_height = al_get_bitmap_height(ball_picture);
	image_width = al_get_bitmap_width(ball_picture);

	pos_x = 320;
	pos_y = 220;
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