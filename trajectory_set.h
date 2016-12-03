#ifndef TRAJECTORY_SET_H
#define TRAJECTORY_SET_H

#include "map_maker.h"

namespace trajectory_set_ns
{

	class Trajectory_set
	{
	public:
		Trajectory_set(int capacity_input);
		~Trajectory_set();
		void clear();
		void resize(int capacity_input);
		int size_of_set(); // return number of trajectories in this set
		void set_trajectory(int index, map_maker_ns::result_path &trajectory_input, double probability_input);
		// get the index-th trajectory, also have the probability of this trajectory
		void get_trajectory(int index, map_maker_ns::result_path &trajectory_output, double &probability_output);
		void add_trajectory(map_maker_ns::result_path &trajectory_input, double probability_input);
	private:
		map_maker_ns::result_path *trajectory_list;
		double *probability;
		int capacity, n;
	};

}

#endif
