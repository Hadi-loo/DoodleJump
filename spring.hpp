#ifndef _SPRING_HPP_
#define _SPRING_HPP_
#include "rsdl.hpp"
using namespace std;

class spring
{
public:
	spring(int, int, int, int);
	int get_x(void);
	int get_y(void);
	void draw_spring(Window*, int);
	bool is_out_of_screen(int);
private:
	int x;
	int y;
	int width;
	int height;
};

#endif