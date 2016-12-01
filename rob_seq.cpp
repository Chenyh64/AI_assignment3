#include "rob_seq.h"
#include "map_maker.h"


namespace rob_seq_ns
{
	seq_route::seq_route(char* filename)
	{
		map.read_text(filename);
		srand((unsigned)time(0));
	}

	seq_route::~seq_route()
	{
		route.clear();
	}

	void seq_route::add_step()
	{

		if (route.size() == 0)
		{
		    rob_step firstCell;
            do
            {
            firstCell.loc_x = rand() % map.map_output.get_col_size();
			firstCell.loc_y = rand() % map.map_output.get_row_size();
            }while(map.map_output.check_available(firstCell.loc_x, firstCell.loc_y)==false);
            route.push_back(firstCell);
        }

		rob_step newCell;
		int dir = trans_model();
		newCell.loc_x = route[route.size()-1].loc_x + DELTA_COL[dir];
		newCell.loc_y = route[route.size()-1].loc_y + DELTA_ROW[dir];
		if (map.map_output.check_available(newCell.loc_x, newCell.loc_y)==false || rand()/double(RAND_MAX) > 0.9){
			newCell.loc_x = route[route.size()-1].loc_x;
			newCell.loc_y = route[route.size()-1].loc_y;
		}
		newCell.action = direc[dir];
		newCell.obs_terrian = obs_model(route[route.size()-1].loc_x, route[route.size()-1].loc_y);

		route.push_back(newCell);
	}


	int seq_route::trans_model()
	{
		int dir;
		dir = rand() % MAX_DIR;
		return dir;
	}

	char seq_route::obs_model(int pos_x, int pos_y)
	{
		char terrian = map.map_output.read_bit(pos_x, pos_y);
		switch(terrian)
		{
            case '1': if (rand()/double(RAND_MAX)<0.9)
                          return UNBLOCKED;
                      else if (rand()/double(RAND_MAX)<0.5)
                          return HIGHWAY;
                      else
                          return HARD_TRAVERSE;
                      break;

            case '2': if (rand()/double(RAND_MAX)<0.9)
                          return HARD_TRAVERSE;
                      else if (rand()/double(RAND_MAX)<0.5)
                          return HIGHWAY;
                      else
                          return UNBLOCKED;
                      break;

            case 'a': if (rand()/double(RAND_MAX)<0.9)
                          return HIGHWAY;
                      else if (rand()/double(RAND_MAX)<0.5)
                          return UNBLOCKED;
                      else
                          return HARD_TRAVERSE;
                      break;

            case 'b': if (rand()/double(RAND_MAX)<0.9)
                          return HIGHWAY;
                      else if (rand()/double(RAND_MAX)<0.5)
                          return UNBLOCKED;
                      else
                          return HARD_TRAVERSE;
                      break;
		}
	}

    void seq_route::write_route(char* filename)
    {
        std::ofstream fout;
        fout.open(filename);
        fout << route[0].loc_x << " " << route[0].loc_y << std::endl;
        for (int i = 1; i < route.size(); ++i)
            fout << route[i].loc_x << " " << route[i].loc_y << std::endl;
        for (int i = 1; i < route.size(); ++i)
            fout << route[i].action << std::endl;
        for (int i = 1; i < route.size(); ++i)
            fout << route[i].obs_terrian << std::endl;

        fout.close();
    }
}
