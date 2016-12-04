#include "filtering_approximator.h"

namespace filtering_approximator_ns
{

	int Filtering_approximator::state_hash(map_maker_ns::map_maker &map_input, int pos_col, int pos_row)
	{
		int res = pos_row * map_input.map_output.get_col_size() + pos_col;
		return res;
	}

	void Filtering_approximator::state_from_hash(int hash_value, int &pos_row, int &pos_col, map_maker_ns::map_maker &map_input)
	{
		pos_row = hash_value / map_input.map_output.get_col_size();
		pos_col = hash_value % map_input.map_output.get_col_size();
	}

	void Filtering_approximator::gen_probability_map(std::unordered_map<int, double> &belief_state, map_maker_ns::map_maker &map_input, probability_map_ns::Probability_map &probability_output)
	{
		int row_size = map_input.map_output.get_row_size(), col_size = map_input.map_output.get_col_size();
		probability_output.clear();
		probability_output.resize(row_size, col_size);
		for (int row = 0; row < row_size; row++)
			for (int col = 0; col < col_size; col++)
			{
				int state = state_hash(map_input, col, row);
				if (belief_state.find(state) == belief_state.end())
					probability_output.set_bit(row, col, 0);
				else
					probability_output.set_bit(row, col, belief_state[state]);
			}
	}

	void Filtering_approximator::solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, double threshold_probability, probability_map_ns::Probability_map &probability_output, probability_map_ns::Probability_map &after10, probability_map_ns::Probability_map &after50)
	{
		int i, j, col, row, map_size = map_input.map_output.get_col_size() * map_input.map_output.get_row_size();
		std::unordered_map<int, double> current_belief, previous_belief;
		current_belief.clear();
		previous_belief.clear();

		for (i = 0; i < map_input.map_output.get_row_size(); i++)
			for (j = 0; j < map_input.map_output.get_col_size(); j++)
			{
				int state = state_hash(map_input, j, i);
				previous_belief[state] = transition_model.prior(j, i, map_input);
			}

		for (i = 0; i < sequence_input.get_size(); i++)
		{
			char previous_action = sequence_input.get_action(i);
			int state, previous_state, previous_row, previous_col, previous_direct;
			double sum_normalize = 0, transition_p;
			std::set<int> possible_current_state;
			possible_current_state.clear();
			current_belief.clear();
			if (previous_action == 'L')
				previous_direct = 0;
			else if (previous_action == 'D')
				previous_direct = 1;
			else if (previous_action == 'R')
				previous_direct = 2;
			else if (previous_action == 'U')
				previous_direct = 3;
			for (auto possible_pre : previous_belief)
			{
				previous_state = possible_pre.first;
				possible_current_state.insert(previous_state);
				state_from_hash(previous_state, previous_row, previous_col, map_input);
				row = previous_row + rob_seq_ns::DELTA_ROW[previous_direct];
				col = previous_col + rob_seq_ns::DELTA_COL[previous_direct];
				if (map_input.map_output.check_available(col, row))
				{
					state = state_hash(map_input, col, row);
					possible_current_state.insert(state);
				}
			}

			for (auto current_state : possible_current_state)
			{
				state_from_hash(current_state, row, col, map_input);
				state = current_state;
				current_belief[state] = 0;	
				// successful action, attention: hard code - direction
				previous_row = row - rob_seq_ns::DELTA_ROW[previous_direct];
				previous_col = col - rob_seq_ns::DELTA_COL[previous_direct];
				if (map_input.map_output.check_available(previous_col, previous_row))
				{
					previous_state = state_hash(map_input, previous_col, previous_row);
					if (previous_belief.find(previous_state) != previous_belief.end())
					{
						transition_p = transition_model.transit_probability(previous_col, previous_row, col, row, previous_action, map_input);
						current_belief[state] += transition_p * previous_belief[previous_state];
					}
				}
				// stay
				if (previous_belief.find(state) != previous_belief.end())
				{
					transition_p = transition_model.transit_probability(col, row, col, row, previous_action, map_input);
					current_belief[state] += transition_p * previous_belief[state];
				}
				current_belief[state] *= sensor_model.sensor_probability(col, row, sequence_input.get_terrain(i), map_input);
				sum_normalize += current_belief[state];
			}

			previous_belief.clear();
			for (auto current_state : possible_current_state)
				if (current_belief[current_state] / sum_normalize > threshold_probability)
					previous_belief[current_state] = current_belief[current_state] / sum_normalize;
			if (i == 9)
				gen_probability_map(previous_belief, map_input, after10);
			if (i == 49)
				gen_probability_map(previous_belief, map_input, after50);
		}

		gen_probability_map(previous_belief, map_input, probability_output);

	}

}

