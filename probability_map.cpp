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
			for (i = 0; i < n_row; ++i)
				if (map_bit[i] != NULL)
				{
					delete[] map_bit[i];
					map_bit[i] = NULL;
				}
			delete[] map_bit;
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

	void Probability_map::get_max(int &pos_row, int &pos_column, double &probability_output)
	{
		int i, j;
		probability_output = -1;
		for (i = 0; i < n_row; i++)
			for (j = 0; j < m_column; j++)
				if (get_bit(i, j) > probability_output)
				{
					probability_output = get_bit(i, j);
					pos_row = i;
					pos_column = j;
				}
	}

	int Probability_map::get_col_size()
	{
		return m_column;
	}

	int Probability_map::get_row_size()
	{
		return n_row;
	}

}








