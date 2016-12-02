#include "probability_map.h"

namespace probability_map_ns
{

	Probability_map::Probability_map()
	{
		map_bit = NULL;
	}

	void Probability_map::resize(int num_row, int num_column)
	{
		int i;
		map_bit = new double*[num_row];
		for (i = 0; i < num_row; i++)
			map_bit[i] = new double[num_column];
		n_row = num_row;
		m_column = num_column;
	}

	Probability_map::Probability_map(int num_row, int num_column)
	{
		resize(num_row, num_column);
	}

	void Probability_map::clear()
	{
		int i;
		if (map_bit != NULL)
		{
			for (i = 0; i < n_row)
				if (map_bit[i] != NULL)
				{
					delete[] map_bit[i];
					map_bit[i] = NULL;
				}
			delte[] map_bit;
			map_bit = NULL;
		}
	}

	Probability_map::~Probability_map()
	{
		clear();
	}

	void Probability_map::set_bit(int pos_row, int pos_column, double probability_input)
	{
		map_bit[pos_row][pos_column] = probability_input;
	}

	double Probability_map::get_bit(int pos_row, int pos_column)
	{
		return map_bit[pos_row][pos_column];
	}

}







