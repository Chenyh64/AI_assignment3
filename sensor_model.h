#ifndef SENSOR_MODEL_H
#define SENSOR_MODEL_H

#include "map_maker.h"

namespace sensor_model_ns
{

	class Sensor_model
	{
	public:
		double sensor_probability(int pos_col, int pos_row, char terrain, map_maker_ns::map_maker &map_input);
	};

}

#endif

