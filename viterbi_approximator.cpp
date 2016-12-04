#include "viterbi_approximator.h"

namespace viterbi_approximator_ns
{

	int Viterbi_approximator::state_hash(int pos_row, int pos_col, map_maker_ns::map_maker &map_input)
	{
		int res = pos_row * map_input.map_output.get_col_size() + pos_col;
		return res;
	}

	void Viterbi_approximator::state_from_hash(int hash_value, int &pos_row, int &pos_col, map_maker_ns::map_maker &map_input)
	{
		pos_col = hash_value % map_input.map_output.get_col_size();
		pos_row = hash_value / map_input.map_output.get_col_size();
	}

	void Viterbi_approximator::top_k_index(std::unordered_map<int, double> &probability, int index_size, int k, std::vector<int> &index_output)
	{
		int i, j, l;
		index_output.clear();
		for (i = 0; i < index_size; i++)
		{
			double p_i;
			if (probability.find(i) == probability.end())
				p_i = 0;
			else
				p_i = probability[i];
			for (j = 0; j < index_output.size(); j++)
			{
				double p_j;
				if (probability.find(index_output[j]) == probability.end())
					p_j = 0;
				else
					p_j = probability[index_output[j]];
				if (p_i > p_j)
					break;
			}
			if (index_output.size() < k)
				index_output.push_back(0);
			for (l = index_output.size() - 1; l > j; l--)
				index_output[l] = index_output[l - 1];
			if (j < index_output.size())
				index_output[j] = i;
		}
	}

	void Viterbi_approximator::gen_trajectory(std::unordered_map<int, int> *trace_back, int end_state, int step_size, map_maker_ns::map_maker &map_input, map_maker_ns::result_path &trajectory_output)
	{
		int i = step_size, cur_state = end_state;
		std::vector<int> reversed_list_col, reversed_list_row;
		reversed_list_col.clear();
		reversed_list_row.clear();
		while (cur_state >= 0)
		{
			int col, row;
			state_from_hash(cur_state, row, col, map_input);
			reversed_list_col.push_back(col);
			reversed_list_row.push_back(row);
			if ((trace_back[i]).find(cur_state) == (trace_back[i]).end())
				break;
			else
				cur_state = trace_back[i--][cur_state];
		}
		trajectory_output.list_row.clear();
		trajectory_output.list_col.clear();
		for (i = reversed_list_col.size() - 1; i >= 0; i--)
		{
			trajectory_output.list_row.push_back(reversed_list_row[i]);
			trajectory_output.list_col.push_back(reversed_list_col[i]);
		}
	}

	void Viterbi_approximator::top_k_trajectory(std::unordered_map<int, double> &probability, std::unordered_map<int, int> *trace_back, int k, int step_size, map_maker_ns::map_maker &map_input, trajectory_set_ns::Trajectory_set &trajectory_output)
	{
		int row_size = map_input.map_output.get_row_size(), col_size = map_input.map_output.get_col_size(), i;
		std::vector<int> top_index;
		top_k_index(probability, row_size * col_size, k, top_index);
		trajectory_output.resize(k);
		for (i = 0; i < k && i < top_index.size(); i++)
		{
			map_maker_ns::result_path path;
			gen_trajectory(trace_back, top_index[i], step_size, map_input, path);
			double p_i;
			if (probability.find(top_index[i]) == probability.end())
				p_i = 0;
			else
				p_i = probability[top_index[i]];
			trajectory_output.add_trajectory(path, p_i);
		}
	}

	void Viterbi_approximator::solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, double threshold_probability, trajectory_set_ns::Trajectory_set &trajectory_output, trajectory_set_ns::Trajectory_set &after10, trajectory_set_ns::Trajectory_set &after50)
	{
		int sequence_size = sequence_input.get_size(), i, j, k, row, col;
		int row_size = map_input.map_output.get_row_size(), col_size = map_input.map_output.get_col_size();
		std::unordered_map<int, int> *trace_state = new std::unordered_map<int, int>[sequence_size + 1];
		std::unordered_map<int, double> *m_message = new std::unordered_map<int, double>[sequence_size + 1];

		(trace_state[0]).clear();
		(m_message[0]).clear();
		for (row = 0; row < row_size; row++)
			for (col = 0; col < col_size; col++)
			{
				int state = state_hash(row, col, map_input);
				trace_state[0][state] = -1;
				m_message[0][state] = transition_model.prior(col, row, map_input);
			}

		for (i = 1; i <= sequence_size; i++)
		{
			char previous_action = sequence_input.get_action(i - 1);
			double sum_normalize = 0;
			int state, previous_direct, previous_col, previous_row, previous_state;
			std::set<int> possible_current_state;
			possible_current_state.clear();
			if (previous_action == 'L')
				previous_direct = 0;
			else if (previous_action == 'D')
				previous_direct = 1;
			else if (previous_action == 'R')
				previous_direct = 2;
			else if (previous_action == 'U')
				previous_direct = 3;
			for (auto previous_pair : m_message[i - 1])
			{
				previous_state = previous_pair.first;
				possible_current_state.insert(previous_state);
				state_from_hash(previous_state, previous_row, previous_col, map_input);
				row = previous_row + rob_seq_ns::DELTA_ROW[previous_direct];
				col = previous_col + rob_seq_ns::DELTA_COL[previous_direct];
				if (map_input.map_output.check_available(col, row))
				{
					state = state_hash(row, col, map_input);
					possible_current_state.insert(state);
				}
			}
			(trace_state[i]).clear();
			(m_message[i]).clear();
			std::unordered_map<int, double> m_current;
			m_current.clear();
			for (auto current_state : possible_current_state)
			{
				state = current_state;
				state_from_hash(state, row, col, map_input);
				if (map_input.map_output.check_available(col, row))
				{
					double max_p, sensor_p, action_p = -1, stay_p;
					int max_state;
					// successfull action, attention - hard code direction
					previous_row = row - rob_seq_ns::DELTA_ROW[previous_direct];
					previous_col = col - rob_seq_ns::DELTA_COL[previous_direct];
					if (map_input.map_output.check_available(previous_col, previous_row))
					{
						previous_state = state_hash(previous_row, previous_col, map_input);
						if ((m_message[i - 1]).find(previous_state) != (m_message[i - 1]).end())
							action_p = transition_model.transit_probability(previous_col, previous_row, col, row, previous_action, map_input) * m_message[i - 1][previous_state];
						else
							action_p = 0;
					}
					// stay
					if ((m_message[i - 1]).find(state) == (m_message[i - 1]).end())
						stay_p = 0;
					else
						stay_p = transition_model.transit_probability(col, row, col, row, previous_action, map_input) * m_message[i - 1][state];
					if (action_p > stay_p)
					{
						max_p = action_p;
						trace_state[i][state] = previous_state;
					}
					else
					{
						max_p = stay_p;
						trace_state[i][state] = state;
					}
					sensor_p = sensor_model.sensor_probability(col, row, sequence_input.get_terrain(i - 1), map_input);
					m_current[state] = sensor_p * max_p;
				}
				sum_normalize += m_current[state];
			}

			for (auto current_state : possible_current_state)
				if (m_current[current_state] / sum_normalize > threshold_probability)
					m_message[i][current_state] = m_current[current_state] / sum_normalize;

			if (i == 10)
				top_k_trajectory(m_message[i], trace_state, 10, 10, map_input, after10);
			if (i == 50)
				top_k_trajectory(m_message[i], trace_state, 10, 50, map_input, after50);
		}

		top_k_trajectory(m_message[sequence_size], trace_state, 10, sequence_size, map_input, trajectory_output);

		delete[] trace_state;
		trace_state = NULL;
		delete[] m_message;
		m_message = NULL;
	}

}








