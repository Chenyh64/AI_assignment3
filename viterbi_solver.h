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
		void solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, tranisition_model_ns::Tranisition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, trajectory_set_ns::Trajectory_set &trajectory_output);
	};

}


#endif
