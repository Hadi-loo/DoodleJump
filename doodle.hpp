#ifndef _DOODLE_HPP_
#define _DOODLE_HPP_
#include "rsdl.hpp"
using namespace std;

class Doodle
{
public:
	Doodle(int x_, int y_, int w,int h,int vx_,int vy_);
	void move();
	void draw_doodle(Window* window, int screen_position);
	bool is_moving();;
	void set_motion_status(int status);
	void set_head_direction(string direction);
	bool is_going_down();
	bool collide_to_platform(int x_,int y_);
	void collision_with_platform(int x_, int y_);
	int get_y();
	bool is_out_of_screen(int screen_position);
	bool collide_to_monster(int x_,int y_);
	bool collide_to_spring(int x_,int y_);
	void collision_with_spring(int x_, int y_);
private:
	int x;
	int y;
	int width;
	int height;
	int vx;
	int vy;
	int motion_status;
	int head_direction;
	int is_jumping;
};

#endif