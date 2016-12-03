#ifndef ROB_SEQ_H
#define ROB_SEQ_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <vector>
#include <fstream>
#include "probability_map.h"


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
	const int DELTA_COL[MAX_DIR] = {-1,  0,  1,  0};
	const int DELTA_ROW[MAX_DIR] = { 0, -1,  0,  1};

    const int amplify_num = 5;
    const int COLOR_ROUTE[3] = { 0,255,0 };


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
			std::vector<Rob_step> route;
		public:
			Seq_route();
			~Seq_route();
			int trans_model();
			char obs_model(int pos_x, int pos_y, map_maker_ns::map_maker &map);
			void add_step(map_maker_ns::map_maker &map);
			void read_route(char* filename);
			void write_route(char* filename);
			int get_size(); // return the size of route
			char get_terrain(int step); // step start from 0
			char get_action(int step); // step start from 0
			void get_location(int &column, int &row, int step); // decide the range of index
            void show_route(cv::Mat &map_img, map_maker_ns::map_maker &map); // show the route on the map
    };

    cv::Mat show_heatMap(probability_map_ns::Probability_map pMap);

}


#endif
