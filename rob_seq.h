#ifndef ROB_SEQ_H
#define ROB_SEQ_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <vector>
#include <fstream>
#include "map_maker.h"

namespace rob_seq_ns
{

	const char BLOCKED = 'B', UNBLOCKED = 'N', HARD_TRAVERSE = 'T', HIGHWAY = 'H';
	const int LEFT = 0, RIGHT = 2, UP = 4, DOWN = 1;
	const char direc[4] = {'L', 'D', 'R', 'U'};
	// directions
	//  3
	//0   2
	//  1
	const int MAX_DIR = 4;
	const int DELTA_COL[MAX_DIR] = {-1,  0,  1,  0} ;
	const int DELTA_ROW[MAX_DIR] = { 0, -1,  0,  1};

	struct Rob_step
	{
		int loc_x;
		int loc_y;
		char obs_terrian;
		char action;
	};

	class Seq_route
	{
		private:
			std::vector<rob_step> route;
		public:
			Seq_route(char* filename);
			~Seq_route();
			int trans_model(map_maker_ns::map_maker &map);
			char obs_model(int pos_x, int pos_y, map_maker_ns::map_maker &map);
			void add_step(map_maker_ns::map_maker &map);
			void read_route(map_maker_ns::map_maker &map);
			void write_route(char* filename, map_maker_ns::map_maker &map);
			int get_size(); // return the size of route
			char get_terrain(int step); // step start from 0
			char get_action(int step); // step start from 0
			void get_location(int &column, int &row); // TODO: decide the range of index
	};

}


#endif
