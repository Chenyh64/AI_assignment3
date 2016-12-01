#include "rob_seq.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("usage: seq_gen map_path text_stored_path \n");
		return 0;
	}

    rob_seq_ns::seq_route newSeq(argv[1]);
    for (int i = 0; i < 10; ++i)
        newSeq.add_step();

    newSeq.write_route(argv[2]);

	return 0;
}

