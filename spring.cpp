#include "spring.hpp"
#include "consts.hpp"

spring::spring(int x_,int y_,int w,int h) 
{
	x = x_;
	y = y_;
	width = w;
	height = h;
}
int spring::get_x()
{
	return x;
}
int spring::get_y()
{
	return y;
} 
void spring::draw_spring(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	window->draw_img(SPRING_FILE_NAME, Rectangle(_x_,_y_,width,height));
}
bool spring::is_out_of_screen(int screen_position)
{
	if (y+height < screen_position - SCREEN_HEIGHT/2)
		return true;
	return false;
}
