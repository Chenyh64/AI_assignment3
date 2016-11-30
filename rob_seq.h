#ifndef ROB_SEQ_H
#define ROB_SEQ_H	

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <vector>
#include "map_maker.h"

namespace rob_seq_ns
{

	const char BLOCKED = 'B', UNBLOCKED = 'N', HARD_TRAVERSE = 'T', UNBLOCKED_HIGHWAY = 'H', HARD_HIGHWAY = 'H';
	const int LEFT = 0, RIGHT = 2, UP = 4, DOWN = 1;
	const char direc[4] = {'L', 'D', 'R', 'U'};
	// directions
	//  3
	//0   2
	//  1
	const int MAX_DIR = 4;
	const int DELTA_COL[MAX_DIR] = {-1,  0,  1,  0} ; 
	const int DELTA_ROW[MAX_DIR] = { 0, -1,  0,  1};



	class rob_step
	{
		int loc_x;
		int loc_y;
		char obs_terrian;
		char action;
	};

	class seq_route
	{	
		private:
			vector<rob_step> route;
			int route_length;
			map_maker_ns::map_maker map;
		public:
			seq_route(char* filename);
			int trans_model();
			int obs_model();
			void add_step();
			void read_route();
			void write_route(); 
	};
 

} 


#endif
