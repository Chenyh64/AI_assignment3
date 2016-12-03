#include "filtering_solver.h"

namespace filtering_ns
{

	int Filtering_solver::state_hash(map_maker_ns::map_maker &map_input, int pos_col, int pos_row)
	{
		int res = pos_row * map_input.map_output.get_col_size() + pos_col;
		return res;
	}

	void Filtering_solver::gen_probability_map(double *belief_state, map_maker_ns::map_maker &map_input, probability_map_ns::Probability_map &probability_output)
	{
		int row_size = map_input.map_output.get_row_size(), col_size = map_input.map_output.get_col_size();
		probability_output.clear();
		probability_output.resize(row_size, col_size);
		for (int row = 0; row < row_size; row++)
			for (int col = 0, col < col_size; col++)
			{
				int state = state_hash(map_input, col, row);
				probability_output.set_bit(row, col, belief_state[state]);
			}
	}

	void Filtering_solver::solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, probability_map_ns::Probability_map &probability_output)
	{
		int i, j, col, row, map_size = map_input.map_output.get_col_size() * map_input.map_output.get_row_size();
		double *current_belief = new double[map_size], *previous_belief = new double[map_size];

		for (i = 0; i < map_input.map_output.get_row_size(); i++)
			for (j = 0; j < map_input.map_output.get_col_size(); j++)
			{
				int state = state_hash(map_input, j, i);
				previous_belief[state] = transition_model.prior(j, i, map_input);
			}

		for (i = 0; i < sequence_input.get_size(); i++)
		{
			double sum_normalize = 0;
			for (row = 0; row < map_input.map_output.get_row_size(); row++)
				for (col = 0; col < map_input.map_output.get_col_size(); col++)
				{
					int state = state_hash(map_input, col, row);
					current_belief[state] = 0;
					for (previous_col = col - 1; previous_col <= col + 1; previous_col++)
						for (previous_row = row - 1; previous_row <= row + 1; previous_row++)
							if (map_input.map_output.check_available(previous_col, previous_row))
							{
								int previous_state = state_hash(map_input, previous_col, previous_row);
								double transition_probability = transition_model.transit_probability(previous_col, previous_row, col, row, sequence_input.get_action(i), map_input);
								current_belief[state] += transition_probability * previous_belief[previous_state];
							}
					current_belief[state] *= sensor_model.sensor_probability(col, row, sequence_input.get_terrain(i), map_input);
					sum_normalize += current_belief[state];
				}
			for (j = 0; j < map_size; j++)
				previous_belief[j] = current_belief[j] / sum_normalize;
			if (i == 9)
				gen_probability_map(previous_belief, map_input, after10);
			if (i == 49)
				gen_probability_map(previous_belief, map_input, after50);
		}

		gen_probability_map(previous_belief, map_input, probability_output);

		delete[] current_belief;
		current_belief = NULL;
		delete[] previous_belief;
		previous_belief = NULL;
	}

}

