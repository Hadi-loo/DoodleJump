#include "doodle.hpp"
#include "consts.hpp"

Doodle::Doodle(int x_, int y_, int w,int h,int vx_,int vy_)
{
	x = x_;
	y = y_;
	width = w;
	height = h;
	vx = vx_;
	vy = vy_;
	is_jumping = 0;
}
void Doodle::move()
{
	y += vy;
	vy -= g;
	if (vy < -PLATFORM_HEIGHT) //           attention!!!
		vy = -PLATFORM_HEIGHT;
	if (motion_status == 1)
		x += V_X;
	else if (motion_status == 2)
		x -= V_X;
	if (x < -width/2)
	{
		x += SCREEN_WIDTH;
	}
	else if (x > SCREEN_WIDTH - width/2)
	{
		x-= SCREEN_WIDTH;
	}
}
void Doodle::draw_doodle(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	if (head_direction == 0)
	{
		if (is_jumping == 0)
		{
			window->draw_img(RIGHT_DOODLE_FILE_NAME, Rectangle(_x_,_y_,width,height));
		}
		else
		{
			window->draw_img(RIGHT_JUMPING_DOODLE_FILE_NAME, Rectangle(_x_,_y_+(height - JUMPING_DOODLE_HEIGHT),width,JUMPING_DOODLE_HEIGHT));
		 	is_jumping++;
		 	if (is_jumping > 6)
		 		is_jumping = 0;
		}
	}
	else
	{
		if (is_jumping == 0)
		{
			window->draw_img(LEFT_DOODLE_FILE_NAME, Rectangle(_x_,_y_,width,height));
		}
		else
		{
			window->draw_img(LEFT_JUMPING_DOODLE_FILE_NAME, Rectangle(_x_,_y_+(height - JUMPING_DOODLE_HEIGHT),width,JUMPING_DOODLE_HEIGHT));
			is_jumping++;
		 	if (is_jumping > 6)
		 		is_jumping = 0;
		}
	}
}
bool Doodle::is_moving()
{
	if ((motion_status == 1) || (motion_status == 2))
		return true;
	return false;
}
void Doodle::set_motion_status(int status)
{
	motion_status = status;
	if (motion_status == 1)
		head_direction = 0;
	else if (motion_status == 2)
		head_direction = 1;
}
void Doodle::set_head_direction(string direction)
{
	if (direction == "right")
		head_direction = 0;
	else if (direction == "left")
		head_direction = 1;
}
bool Doodle::is_going_down()
{
	if (vy <= 0)
		return true;
	return false;
}
bool Doodle::collide_to_platform(int x_,int y_)
{
	if ((x >= x_ - width) && (x <= x_ + PLATFORM_WIDTH))
	{
		if ((y >= y_) && (y <= y_ + PLATFORM_HEIGHT))
		{
			return true;
		}
	}
	return false;
}
void Doodle::collision_with_platform(int x_, int y_)
{
	y = y_ + PLATFORM_HEIGHT;
	vy = V0_Y;
	is_jumping = 1;
}
int Doodle::get_y()
{
	return y;
}
bool Doodle::is_out_of_screen(int screen_position)
{
	if (y+height < screen_position - SCREEN_HEIGHT/2)
		return true;
	return false;
}
bool Doodle::collide_to_monster(int x_,int y_)
{
	if ((x + width >= x_) && (x <= x_ + MONSTER_WIDTH))
	{
		if ((y + height >= y_) && (y <= y_ + MONSTER_HEIGHT))
		{
			return true;
		}
	}
	return false;
}
bool Doodle::collide_to_spring(int x_,int y_)
{
	if ((x >= x_ - width) && (x <= x_ + SPRING_WIDTH))
	{
		if ((y >= y_) && (y <= y_ + SPRING_HEIGHT))
		{
			return true;
		}
	}
	return false;
}
void Doodle::collision_with_spring(int x_, int y_)
{
	y = y_ + SPRING_HEIGHT;
	vy = 2*V0_Y;
	is_jumping = 1;
}