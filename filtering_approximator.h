#ifndef FILTERING_APPROXIMATOR_H
#define FILTERING_APPROXIMATOR_H

#include "rob_seq.h"
#include "transition_model.h"
#include "sensor_model.h"
#include "probability_map.h"
#include <unordered_map>
#include <set>

namespace filtering_approximator_ns
{

	class Filtering_approximator
	{
	public:
		void solve(map_maker_ns::map_maker &map_input, rob_seq_ns::Seq_route &sequence_input, transition_model_ns::Transition_model &transition_model, sensor_model_ns::Sensor_model &sensor_model, double threshold_probability, probability_map_ns::Probability_map &probability_output, probability_map_ns::Probability_map &after10, probability_map_ns::Probability_map &after50);
	private:
		int state_hash(map_maker_ns::map_maker &map_input, int pos_col, int pos_row);
		void state_from_hash(int hash_value, int &pos_row, int &pos_col, map_maker_ns::map_maker &map_input);
		void gen_probability_map(std::unordered_map<int, double> &belief_state, map_maker_ns::map_maker &map_input, probability_map_ns::Probability_map &probability_output);
	};

}

#endif
