#include "platform.hpp"
#include "consts.hpp"

platform::platform(int x_,int y_,int w,int h) 
{
	x = x_;
	y = y_;
	width = w;
	height = h;
}
void platform::draw_platform(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	window->draw_img(PLATFORM_FILE_NAME, Rectangle(_x_,_y_,width,height));
}
int platform::get_x()
{
	return x;
}
int platform::get_y()
{
	return y;
}
bool platform::is_out_of_screen(int screen_position)
{
	if (y+height < screen_position - SCREEN_HEIGHT/2)
		return true;
	return false;
}
void platform::update_platform()
{
	return;
}
bool platform::is_bplatform()
{
	return false;
}
void platform::break_platform()
{
	return;
}
//===========================================================================================
mplatform::mplatform(int x_,int y_,int w,int h)
: platform(x_, y_, w, h)
{
	vx = PLATFORM_SPEED;
}
void mplatform::update_platform()
{
	x += vx;
	if (x + width > SCREEN_WIDTH)
	{
		vx *= -1;
		x = (SCREEN_WIDTH - width) - (x + width - SCREEN_WIDTH);
	} 
	else if (x < 0)
	{
		vx *= -1;
		x = -x;
	}
}
void mplatform::draw_platform(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	window->draw_img(MPLATFORM_FILE_NAME, Rectangle(_x_,_y_,width,height));
}
//===========================================================================================
bplatform::bplatform(int x_,int y_,int w,int h)
: platform(x_, y_, w, h)
{
	is_breaked = false;
	breaking_status = 0;
}

void bplatform::update_platform()
{
	if (is_breaked)
	{
		breaking_status++;
	}
}
bool bplatform::is_bplatform()
{
	return true;
}
void bplatform::break_platform()
{
	is_breaked = true;
}
void bplatform::draw_platform(Window* window, int screen_position)
{
	int _x_ = x;
	int _y_ = (SCREEN_HEIGHT-(y-(screen_position - SCREEN_HEIGHT/2)))-height;
	if (!is_breaked)
	{
		window->draw_img(BPLATFORM_FILE_NAME, Rectangle(_x_,_y_,width,height));
	}
	else
	{
		if (breaking_status < 2)
		{
			window->draw_img(BPLATFORM1_FILE_NAME, Rectangle(_x_,_y_,width,BPLATFORM1_HEIGHT));
		}
		else if (breaking_status < 4)
		{
			window->draw_img(BPLATFORM2_FILE_NAME, Rectangle(_x_,_y_,width,BPLATFORM2_HEIGHT));
		}
		else if (breaking_status < 6)
		{
			window->draw_img(BPLATFORM3_FILE_NAME, Rectangle(_x_,_y_,width,BPLATFORM3_HEIGHT));
		}
	}
}