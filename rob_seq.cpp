#include "rob_seq.h"

namespace rob_seq_ns
{
	Seq_route::Seq_route()
	{
		srand((unsigned)time(0));
	}

	Seq_route::~Seq_route()
	{
		route.clear();
	}

	void Seq_route::add_step(map_maker_ns::map_maker& map)
	{

		if (route.size() == 0)
		{
		    Rob_step firstCell;
            do
            {
                firstCell.loc_x = rand() % map.map_output.get_col_size();
			    firstCell.loc_y = rand() % map.map_output.get_row_size();
            }while(map.map_output.check_available(firstCell.loc_x, firstCell.loc_y)==false);
            route.push_back(firstCell);
        }

		Rob_step newCell;
		int dir = trans_model();
		newCell.loc_x = route[route.size()-1].loc_x + DELTA_COL[dir];
		newCell.loc_y = route[route.size()-1].loc_y + DELTA_ROW[dir];
		if (map.map_output.check_available(newCell.loc_x, newCell.loc_y)==false || ((double)(rand()/(RAND_MAX)) > 0.9)){
			newCell.loc_x = route[route.size()-1].loc_x;
			newCell.loc_y = route[route.size()-1].loc_y;
		}
		newCell.action = direc[dir];
		newCell.obs_terrian = obs_model(route[route.size()-1].loc_x, route[route.size()-1].loc_y, map);

		route.push_back(newCell);
    }


	int Seq_route::trans_model()
	{
		int dir;
		dir = rand() % MAX_DIR;
		return dir;
	}

	char Seq_route::obs_model(int pos_x, int pos_y, map_maker_ns::map_maker& map)
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

    void Seq_route::write_route(char* filename)
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

    void Seq_route::read_route(char* filename)
    {
        std::ifstream fin;
        fin.open(filename);
        Rob_step firstCell;
        fin >> firstCell.loc_x >> firstCell.loc_y;
        route.push_back(firstCell);

        for (int i = 1; i <= 100; ++i)
        {
            Rob_step newCell;
            fin >> newCell.loc_x >> newCell.loc_y;
            route.push_back(newCell);
        }

        for (int i = 1; i <= 100; ++i)
        {
            fin >> route[i].action;
        }

        for (int i = 1; i <= 100; ++i)
        {
            fin >> route[i].obs_terrian;
        }

        fin.close();
    }

    int Seq_route::get_size()
    {
        return route.size();
    }

    char Seq_route::get_terrain(int step)
    {
        return route[step].obs_terrian;
    }

    char Seq_route::get_action(int step)
    {
        return route[step].action;
    }

    void Seq_route::get_location(int& column, int &row, int step)
    {
        column = route[step].loc_x;
        row = route[step].loc_y;
    }

    void Seq_route::show_route(cv::Mat& map_img, map_maker_ns::map_maker& map)
    {
        for (int k = 0; k < amplify_num; ++k)
            for (int h = 0; h < amplify_num; ++h)
                for (int i = 0; i < route.size(); ++i)
                {
                    map_img.at<cv::Vec3b>((map.map_output.get_row_size() - 1 - route[i].loc_y)*amplify_num + k, route[i].loc_x*amplify_num + h)[0] = COLOR_ROUTE[2];
                    map_img.at<cv::Vec3b>((map.map_output.get_row_size() - 1 - route[i].loc_y)*amplify_num + k, route[i].loc_x*amplify_num + h)[1] = COLOR_ROUTE[1];
                    map_img.at<cv::Vec3b>((map.map_output.get_row_size() - 1 - route[i].loc_y)*amplify_num + k, route[i].loc_x*amplify_num + h)[2] = COLOR_ROUTE[0];
                }
    }

    cv::Mat show_heatMap(probability_map_ns::Probability_map &pMap)
    {
        int amplify_num = 5;
		cv::Mat pMap_img(pMap.get_row_size() * amplify_num, pMap.get_col_size() * amplify_num\
			,CV_8UC1, cv::Scalar( 0 ));


        double maxValue;
        int locX=0, locY=0;
        pMap.get_max(locY, locX, maxValue);

        for (int i = 0; i < pMap.get_row_size(); ++i)
            for (int j = 0; j < pMap.get_col_size(); ++j)
                for (int k = 0; k < amplify_num; ++k)
                    for (int h = 0; h < amplify_num; ++h)
                    {
                        pMap_img.at<uchar>((pMap.get_row_size() - 1 - i)*amplify_num + k, j*amplify_num + h) = 255 * pMap.get_bit(i, j)/maxValue;
                        //std::cout << 255*pMap.get_bit(i, j)/maxValue << std::endl;
                        //std::cout << i << " " << j << " " << k << " " << h << std::endl;
                    }
       // cv::namedWindow("xxx");
       // cv::imshow("xxx", pMap_img);
       // cv::waitKey();
        cv::Mat heatMap;
        cv::applyColorMap(pMap_img, heatMap, 2);

        return heatMap;
    }

}
