#ifndef TRAJECTORY_SET_H
#define TRAJECTORY_SET_H

#include "map_maker.h"

namespace trajectory_set_ns
{

	class Trajectory_set
	{
	public:
		Trajectory_set(int n_trajectory);
		~Trajectory_set();
		clear();
		int size_of_set(); // return number of trajectories in this set
		void set_trajectory(int index, map_maker_ns::result_path &trajectory_input, double probability_input);
		// get the index-th trajectory, also have the probability of this trajectory
		void get_trajectory(int index, map_maker_ns::result_path &trajectory_output, double &probability_output);
	private:
		map_maker_ns::result_path *trajectory_list;
		double *probability;
	};

}

#endif
