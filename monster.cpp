#include "monster.hpp"
#include "consts.hpp"

monster::monster(int x_,int y_,int w,int h) 
{
	x = x_;
	y = y_;
	width = w;
	height = h;
}
void monster::draw_monster(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	window->draw_img(MONSTER_FILE_NAME, Rectangle(_x_,_y_,width,height));
}
bool monster::is_out_of_screen(int screen_position)
{
	if (y+height < screen_position - SCREEN_HEIGHT/2)
		return true;
	return false;
}
int monster::get_x(void)
{
	return x;
}
int monster::get_y(void)
{
	return y;
}

