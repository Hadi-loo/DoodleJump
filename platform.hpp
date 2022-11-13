#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_
#include "rsdl.hpp"
using namespace std;

class platform 
{
public:
	platform(int,int,int,int);
	virtual void draw_platform(Window*, int);
	int get_x();
	int get_y();
	bool is_out_of_screen(int);
	virtual void update_platform();
	virtual bool is_bplatform();
	virtual void break_platform();
protected:
	int x;
	int y;
	int width;
	int height;
};

class mplatform : public platform
{
public:
	mplatform(int,int,int,int);
	void update_platform();
	void draw_platform(Window* window, int screen_position);
private:
	int vx;
};

class bplatform : public platform
{
public:
	bplatform(int,int,int,int);
	void update_platform();
	bool is_bplatform();
	void break_platform();
	void draw_platform(Window*,int);
private:
	bool is_breaked;
	int breaking_status;
};

#endif