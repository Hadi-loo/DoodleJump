#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_
#include "rsdl.hpp"
using namespace std;

class monster
{
public:
	monster(int ,int ,int ,int);
	void draw_monster(Window*, int);
	bool is_out_of_screen(int);
	int get_x();
	int get_y();
private:
	int x;
	int y;
	int width;
	int height;
};

#endif