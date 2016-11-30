#include "rob_seq.h"

namespace rob_seq_ns
{
	seq_route::seq_route(char* filename)
	{	
		int route_length = 0;
		map.read_text(filename);
	}

	~seq_route::seq_route()
	{
		route.clear();
	}

	void seq_route::add_step()
	{	
		if (route_length == 0)
		{
			
		}
		else
		{

		}
	}





}
