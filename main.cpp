#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include "rsdl.hpp"
#include "consts.hpp"
#include "doodle.hpp"
#include "platform.hpp"
#include "monster.hpp"
#include "spring.hpp"
using namespace std;
//=========================================================================================================================================
struct sequence
{	
	int start;
	int end;
	int total_height;
	int number_of_entities;
};
//=========================================================================================================================================
void make_platforms(vector <platform*> *platforms, vector <monster*> *monsters, vector <spring*> *springs, int &maximum_height, int line_number)
{
	ifstream input_file(MAP_FILE_NAME);
	string line;
	for (int i = 0; i < line_number; i++)
	{
		getline(input_file, line);
	}
	getline(input_file, line);
	stringstream LiNe(line);
	int number_of_entities;
	int total_height;
	LiNe >> number_of_entities;
	LiNe >> number_of_entities;
	LiNe >> total_height;
	LiNe >> number_of_entities;
	int _x_;
	int _y_;
	string _type_;
	for (int i = 0; i < number_of_entities; i++)
	{
		getline(input_file, line);
		stringstream LiNe(line);
		LiNe >> _x_;
		LiNe >> _y_;
		LiNe >> _type_;
		if (_type_ == "platform")
			platforms->push_back(new platform(_x_ - PLATFORM_WIDTH/2, maximum_height + _y_, PLATFORM_WIDTH, PLATFORM_HEIGHT));
		else if (_type_ == "mplatform")
			platforms->push_back(new mplatform(_x_ - PLATFORM_WIDTH/2, maximum_height + _y_, PLATFORM_WIDTH, PLATFORM_HEIGHT));
		else if (_type_ == "bplatform")
			platforms->push_back(new bplatform(_x_ - PLATFORM_WIDTH/2, maximum_height + _y_, PLATFORM_WIDTH, PLATFORM_HEIGHT));
		else if (_type_ == "enemy")
			monsters->push_back(new monster(_x_ - MONSTER_WIDTH/2, maximum_height + _y_, MONSTER_WIDTH, MONSTER_HEIGHT));
		else if (_type_ == "spring")
			springs->push_back(new spring(_x_ - SPRING_WIDTH/2, maximum_height + _y_, SPRING_WIDTH, SPRING_HEIGHT));
	}
	maximum_height += total_height;
}

void game_over(Window* window, int score)
{
	window->clear();
	window->draw_img(BACKGROUND_FILE_NAME);
	stringstream ss;
	ss << score;
	window->show_text("Score:", Point(SCREEN_WIDTH/2-200, SCREEN_HEIGHT/2-300), BLACK, "FreeSans.ttf", 80);
	window->show_text(ss.str(), Point(SCREEN_WIDTH/2-140, SCREEN_HEIGHT/2-200), BLACK, "FreeSans.ttf", 80);
	window->update_screen();
	while (true)
	{
		while (window->has_pending_event())
		{
			Event e = window->poll_for_event();
			Event::EventType event_type = e.get_type();
			if (event_type == Event::QUIT)
			{
				exit(0);
			}
			else if (event_type == Event::KEY_PRESS)
			{
				exit(0);
			} 
		}
	}
}

int create_sequences(vector <sequence*> &sequences)
{
	ifstream input_file(MAP_FILE_NAME);
	string line;
	int number_of_sequences;
	getline(input_file, line);
	stringstream LiNe(line);
	LiNe >> number_of_sequences;
	for (int i = 0; i < number_of_sequences; i++)
	{
		sequences.push_back(new sequence);
		getline(input_file, line);
		stringstream LiNe(line);
		LiNe >> (sequences[i])->start;
		LiNe >> (sequences[i])->end;
		LiNe >> (sequences[i])->total_height;
		LiNe >> (sequences[i])->number_of_entities;
		for (int j = 0; j < (sequences[i])->number_of_entities; j++)
		{
			getline(input_file, line);
		}
		getline(input_file, line);
	}
	return number_of_sequences;
}

int find_sequence(vector <sequence*> sequences, int score)
{
	vector <int> possible_sequences;
	for (int i = 0; i < sequences.size(); i++)
		if (score >= sequences[i]->start)
			if ((score <= sequences[i]->end) || (sequences[i]->end == -1))
				possible_sequences.push_back(i);
	srand(time(0));
	int index = (rand()) % (possible_sequences.size());
	return possible_sequences[index];			
}

int find_line(vector <sequence*> sequences, int sequence_number)
{
	int line_number = 1;
	for (int i = 0; i < sequence_number; i++)
	{
		line_number += sequences[i]->number_of_entities + 2; 
	}
	return line_number;
}

void update(Window* window, Doodle* doodle, vector <platform*> &platforms, vector <monster*> &monsters, vector <spring*> &springs, int &score, int &screen_position, int &maximum_height, int &plat_str_index, int &mon_str_index, int &spr_str_index, vector <sequence*> sequences)
{
	while (window->has_pending_event())
	{
		Event e = window->poll_for_event();
		Event::EventType event_type = e.get_type();
		if (event_type == Event::QUIT)
		{
			exit(0);
		}
		else if (event_type == Event::KEY_RELEASE)
		{
			doodle->set_motion_status(0);
		}
		else if (event_type == Event::KEY_PRESS)
		{
			char ch = e.get_pressed_key();
			if (ch == 'd' || ch == 'D')
			{
				doodle->set_motion_status(1);
			}
			else if (ch == 'a' || ch == 'A')
			{
				doodle->set_motion_status(2);
			}
		}
	}
	doodle->move();
	int plat_from = plat_str_index;
	for (int i = plat_from; i<platforms.size();i++)
	{
		if (platforms[i]->is_out_of_screen(screen_position))
			plat_str_index = i;
		else
			platforms[i]->update_platform();
	}
	plat_from = plat_str_index;
	for (int i = plat_from; i<platforms.size();i++)
	{
		if (doodle->is_going_down())
		{
			if (doodle->collide_to_platform(platforms[i]->get_x(), platforms[i]->get_y()))
			{
				if (!(platforms[i]->is_bplatform()))
				{
					doodle->collision_with_platform(platforms[i]->get_x(),platforms[i]->get_y());
					break;
				}
				else
					platforms[i]->break_platform();
			}
		}
	}
	int mon_from = mon_str_index;
	for (int i = mon_from; i<monsters.size();i++)
	{
		if (monsters[i]->is_out_of_screen(screen_position))
			mon_str_index = i;
		if (doodle->collide_to_monster(monsters[i]->get_x(), monsters[i]->get_y()))
				game_over(window, score);
	}

	int spr_from = spr_str_index;
	for (int i = spr_from; i<springs.size();i++)
	{
		if (springs[i]->is_out_of_screen(screen_position))
			spr_str_index = i;
		if (doodle->is_going_down())
		{
			if (doodle->collide_to_spring(springs[i]->get_x(), springs[i]->get_y()))
			{
				doodle->collision_with_spring(springs[i]->get_x(), springs[i]->get_y());
				break;
			}
		}
	}

	if (doodle->get_y() > score)
		score = doodle->get_y();
	if (doodle->get_y() > screen_position)
		screen_position = doodle->get_y();
	if (screen_position > maximum_height - SCREEN_HEIGHT/2)
	{
		int sequence_number = find_sequence(sequences, score);
		int line_number = find_line(sequences, sequence_number);
		make_platforms(&platforms, &monsters, &springs, maximum_height, line_number);
	}
	if (doodle->is_out_of_screen(screen_position))
		game_over(window, score);
}

void draw(Window* window, Doodle* doodle, vector <platform*> platforms, vector <monster*> monsters, vector <spring*> springs, int screen_position, int score)
{
	window->clear();
	window->draw_img(BACKGROUND_FILE_NAME);
	for (auto x : platforms)
	{
		x->draw_platform(window, screen_position);
	}
	for (auto x : monsters)
	{
		x->draw_monster(window, screen_position);
	}
	for (auto x : springs)
	{
		x->draw_spring(window, screen_position);
	}
	doodle->draw_doodle(window, screen_position);
	stringstream ss;
	ss << score;
	window->show_text("Score: " + ss.str(), Point(10,10), BLACK, "FreeSans.ttf", 24);
	window->update_screen();
}
//=========================================================================================================================================
int main()
{
	vector <platform*> platforms;
	vector <monster*> monsters;
	vector <spring*> springs;
	vector <sequence*> sequences;
	Doodle doodle(SCREEN_WIDTH/2 - DOODLE_WIDTH/2, SCREEN_HEIGHT/2, DOODLE_WIDTH, DOODLE_HEIGHT, 0, V0_Y);
	int maximum_height = 0;
	int platforms_starting_index = 0;
	int monsters_starting_index = 0;
	int springs_starting_index = 0;
	int score = 0;
	
	int number_of_sequences = create_sequences(sequences);
	int sequence_number = find_sequence(sequences, score);
	int line_number = find_line(sequences, sequence_number);
	make_platforms(&platforms, &monsters, &springs, maximum_height, line_number);
	
	Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Doodle Jump!");
	int screen_position = SCREEN_HEIGHT/2;
	while (true)
	{
		update(window, &doodle, platforms, monsters, springs, score, screen_position, maximum_height, platforms_starting_index, monsters_starting_index, springs_starting_index, sequences);
		draw(window, &doodle, platforms, monsters, springs, screen_position, score);
		delay(20);
	}
	return 0;
}