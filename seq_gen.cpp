#include "rob_seq.h"

int main(int argc, char* argv[])
{


	if (argc < 2)
	{
		printf("usage: seq_gen map_path text_stored_path show_image(y/n)\n");
		return 0;
	}

    map_maker_ns::map_maker map;
    map.read_text(argv[1]);

    rob_seq_ns::Seq_route seq;
    for (int i = 0; i < 100; ++i)
        seq.add_step(map);

    seq.write_route(argv[2]);

    if (argc == 4 && strcmp(argv[3], "y")==0)
    {
     cv::Mat map_img = map.show_map_img();

    seq.show_route(map_img, map);

    cv::namedWindow("map");
    cv::imshow("map", map_img);

    }

/*
    map_maker_ns::map_maker map;
    map.read_text("../1");

    cv::Mat map_img = map.show_map_img();

    rob_seq_ns::Seq_route newSeq;

    // create a new random route
    for (int i = 0; i < 100; ++i)
        newSeq.add_step(map);

    newSeq.write_route("../2");
    newSeq.show_route(map_img, map);

    cv::namedWindow("map");
    cv::imshow("map", map_img);

    cv::Mat new_map_img = map.show_map_img();

    // use an exist map
    newSeq.read_route("../2");
    newSeq.show_route(new_map_img, map);

    cv::namedWindow("new_map");
    cv::imshow("new_map", new_map_img);
    cv::waitKey();
*/





	return 0;
}

