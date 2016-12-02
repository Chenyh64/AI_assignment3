#ifndef TRANSITION_MODEL_H
#define TRANSITION_MODEL_H

#include "map_maker.cpp"
#include "rob_seq.h"

namespace tranisition_model_ns
{

	class Tranisition_model
	{
	public:
		double prior(int pos_col, int pos_row, map_maker_ns::map_maker &map_input);
		double transit_probability(int from_col, int from_row, int to_col, int to_row, char action, map_maker_ns::map_maker &map_input);
	};

}

#endif