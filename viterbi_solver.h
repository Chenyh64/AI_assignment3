#ifndef VITERBI_SOLVER_H
#define VITERBI_SOLVER_H

#include "map_maker.h"
#include "rob_seq.h"
#include "transition_model.h"
#include "sensor_model.h"
#include "trajectory_set.h"

namespace viterbi_solver_ns
{

	class Viterbi_solver
	{
	public:
		void solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, trajectory_set_ns::Trajectory_set &trajectory_output, trajectory_set_ns::Trajectory_set &after10, trajectory_set_ns::Trajectory_set &after50);
	private:
		int state_hash(int pos_row, int pos_col, map_maker_ns::map_maker &map_input);
		void state_from_hash(int hash_value, int &pos_row, int &pos_col, map_maker_ns::map_maker &map_input);
		void top_k_index(double *probability, int index_size, int k, std::vector<int> &index_output);
		void gen_trajectory(int **trace_back, int end_state, int step_size, map_maker_ns::map_maker &map_input, map_maker_ns::result_path &trajectory_output);
		void top_k_trajectory(double *probability, int **trace_back, int k, int step_size, map_maker_ns::map_maker &map_input, trajectory_set_ns::Trajectory_set &trajectory_output);
	};

}


#endif
