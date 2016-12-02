#include "sensor_model.h"

namespace sensor_model_ns
{

	double Sensor_model::sensor_probability(int pos_col, int pos_row, char terrain, map_maker_ns::map_maker &map_input)
	{
		if (!map_input.map_output.check_available(pos_col, pos_row))
			return 0;
		char current_terrain_raw = map_input.map_output.read_bit(pos_col, pos_row), current_terrain;
		if (current_terrain_raw == '0')
			current_terrain = 'B'; // blocked
		else if (current_terrain_raw == '1')
			current_terrain = 'N'; // normal
		else if (current_terrain_raw == '2')
			current_terrain = 'T'; // hard to traverse
		else if (current_terrain_raw == 'a' || current_terrain_raw == 'b')
			current_terrain = 'H'; // highway
		if (terrain == 'B')
			return 0;
		else if (terrain == current_terrain)
			return 0.9;
		else
			return 0.05;		
	}

}
