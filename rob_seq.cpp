#include "rob_seq.h"

namespace rob_seq_ns
{
	seq_route::seq_route(char* filename)
	{	
		map.read_text(filename);
		srand((unsigned)time(0));
	}

	~seq_route::seq_route()
	{
		route.clear();
	}

	void seq_route::add_step()
	{
		rob_step newCell;
		if (route.size() == 0)
		{
			newCell.loc_x = rand() % map.get_col_size();
			newCell.loc_y = rand() % map.get_row_size();
		}
		else
		{
			int dir = trans_model();
			newCell.loc_x = route[route.size()-1].loc_x + DELTA_COL[dir];
			newCell.loc_y = route[route.size()-1].loc_y + DELTA_ROW[dir];
			if (!map.check_available(newCell.loc_x, newCell.loc_y) || rand()/double(RAND_MAX) > 0.9){
				newCell.loc_x = route[route.size()-1].loc_x;
				newCell.loc_y = route[route.size()-1].loc_y;
			}
			newCell.action = direc[dir];
			newCell.obs_terrian = obs_model();		
		}
		route.push_back(newCell);
	}





}
