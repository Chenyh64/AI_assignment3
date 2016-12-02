#include "transition_model.h"

namespace tranisition_model_ns
{

	double Tranisition_model::prior(int pos_col, int pos_row, map_maker_ns::map_maker &map_input)
	{
		int available_cells = map_input.map_output.get_available_cell_num();
		double res = double(1) / double(available_cells);
		if (!map_input.map_output.check_available(pos_col, pos_row))
			return 0;
		return res;
	}

	double Tranisition_model::transit_probability(int from_col, int from_row, int to_col, int to_row, char action, map_maker_ns::map_maker &map_input)
	{
		if (!map_input.map_output.check_available(to_col, to_row))
			return 0;
		int delta_col, delta_row, action_direction, target_col, target_row;
		bool target_is_available;
		if (action == 'L')
			action_direction = 0;
		else if (action == 'D')
			action_direction = 1;
		else if (action == 'R')
			action_direction = 2;
		else
			action_direction = 3;
		delta_col = rob_seq_ns::DELTA_COL[action_direction];
		delta_row = rob_seq_ns::DELTA_ROW[action_direction];
		target_col = from_col + delta_col;
		target_row = from_row + delta_row;
		if (!(to_col == target_col && to_row == target_row) && !(to_col == from_col && to_row == from_row))
			return 0;
		target_is_available = map_input.map_output.check_available(target_col, target_row);
		if (to_col == target_col && to_row == target_row)
		{
			if (target_is_available)
				return 0.9;
			else
				return 0;
		}
		else if (to_col == from_col && to_row == from_row)
		{
			if (target_is_available)
				return 0.1;
			else
				return 1;
		}
	}

}
