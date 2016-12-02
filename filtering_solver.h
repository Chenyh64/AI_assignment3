#ifndef FILTERING_SOLVER_H
#define FILTERING_SOLVER_H

#include "map_maker.h"
#include "rob_seq.h"
#include "transition_model.h"
#include "sensor_model.h"
#include "probability_map.h"

namespace filtering_ns
{

	class Filtering_solver
	{
	public:
		void solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, tranisition_model_ns::Tranisition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, probability_map_ns::Probability_map &probability_output);
	};

}

#endif
