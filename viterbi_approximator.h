#ifndef VITERBI_APPROXIMATOR_H
#define VITERBI_APPROXIMATOR_H

#include "map_maker.h"
#include "rob_seq.h"
#include "transition_model.h"
#include "sensor_model.h"
#include "trajectory_set.h"
#include <unordered_map>
#include <set>

namespace viterbi_approximator_ns
{

	class Viterbi_approximator
	{
	public:
		void solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, double threshold_probability, trajectory_set_ns::Trajectory_set &trajectory_output, trajectory_set_ns::Trajectory_set &after10, trajectory_set_ns::Trajectory_set &after50);
	private:
		int state_hash(int pos_row, int pos_col, map_maker_ns::map_maker &map_input);
		void state_from_hash(int hash_value, int &pos_row, int &pos_col, map_maker_ns::map_maker &map_input);
		void top_k_index(std::unordered_map<int, double> &probability, int index_size, int k, std::vector<int> &index_output);
		void gen_trajectory(std::unordered_map<int, int> *trace_back, int end_state, int step_size, map_maker_ns::map_maker &map_input, map_maker_ns::result_path &trajectory_output);
		void top_k_trajectory(std::unordered_map<int, double> &probability, std::unordered_map<int, int> *trace_back, int k, int step_size, map_maker_ns::map_maker &map_input, trajectory_set_ns::Trajectory_set &trajectory_output);
	};

}


#endif
