#include "trajectory_set.h"

namespace trajectory_set_ns
{

	Trajectory_set::Trajectory_set(int capacity_input)
	{
		capacity = capacity_input;
		n = 0;
		trajectory_list = new map_maker_ns::result_path[capacity];
		probability = new double[capacity];
	}

	void Trajectory_set::clear()
	{
		if (trajectory_list != NULL)
			delete[] trajectory_list;
		trajectory_list = NULL;
		if (probability != NULL)
			delete[] probability;
		probability = NULL;
	}

	Trajectory_set::~Trajectory_set()
	{
		clear();
	}

	void Trajectory_set::resize(int capacity_input)
	{
		clear();
		capacity = capacity_input;
		n = 0;
		trajectory_list = new map_maker_ns::result_path[capacity];
		probability = new double[capacity];
	}

	int Trajectory_set::size_of_set()
	{
		return n;
	}

	void Trajectory_set::set_trajectory(int index, map_maker_ns::result_path &trajectory_input, double probability_input)
	{
		int i;
		probability[index] = probability_input;
		(trajectory_list[index]).list_row.clear();
		(trajectory_list[index]).list_col.clear();
		for (i = 0; i < trajectory_input.list_row.size(); i++)
		{
			(trajectory_list[index]).list_row.push_back(trajectory_input.list_row[i]);
			(trajectory_list[index]).list_col.push_back(trajectory_input.list_col[i]);
		}
	}

	void Trajectory_set::get_trajectory(int index, map_maker_ns::result_path &trajectory_output, double &probability_output)
	{
		int i;
		probability_output = probability[index];
		trajectory_output.list_row.clear();
		trajectory_output.list_col.clear();
		for (i = 0; i < (trajectory_list[index]).list_row.size(); i++)
		{
			trajectory_output.list_row.push_back((trajectory_list[index]).list_row[i]);
			trajectory_output.list_col.push_back((trajectory_list[index]).list_col[i]);
		}
	}

	void Trajectory_set::add_trajectory(map_maker_ns::result_path &trajectory_input, double probability_input)
	{
		int index, i;
		for (index = 0; index < n; index++)
			if (probability_input > probability[index])
				break;
		if (n < capacity)
			n++;
		for (i = n - 1; i > index; i--)
			set_trajectory(i, trajectory_list[i - 1], probability[i - 1]);
		if (index < capacity)
			set_trajectory(index, trajectory_input, probability_input);
	}

}







