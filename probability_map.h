#ifndef PROBABILITY_MAP_H
#define PROBABILITY_MAP_H

#include "map_maker.h"

namespace probability_map_ns
{

	class Probability_map
	{
	public:
		Probability_map();
		Probability_map(int num_row, int num_column);
		~Probability_map();
		void clear();
		void resize(int num_row, int num_column);
		void set_bit(int pos_row, int pos_column, double probability_input);
		double get_bit(int pos_row, int pos_column);
		void get_max(int &pos_row, int &pos_column, double &probability_output);
	private:
		double **map_bit;
		int n_row, m_column;
	};

}

#endif
