#include "filtering_solver.h"
#include "transition_model.h"
#include "sensor_model.h"
#include "rob_seq.h"

int main(int argc, char* argv[])
{

    map_maker_ns::map_maker map;
    map.read_text(argv[1]);

    rob_seq_ns::Seq_route route;
    route.read_route(argv[2]);

    transition_model_ns::Transition_model transition_model;
    sensor_model_ns::Sensor_model sensor_model;
    probability_map_ns::Probability_map pOutput;
    probability_map_ns::Probability_map pOutput10;
    probability_map_ns::Probability_map pOutput50;

    filtering_ns::Filtering_solver fSolver;
    fSolver.solve(map, route, transition_model, sensor_model, pOutput, pOutput10, pOutput50);

    cv::Mat heatMap;
    heatMap = rob_seq_ns::show_heatMap(pOutput);
    cv::namedWindow("heatMap100");
    cv::imshow("heatMap100", heatMap);

    cv::Mat map_img;
    map_img = map.show_map_img();
    route.show_route(map_img, map);
    cv::namedWindow("map");
    cv::imshow("map", map_img);

    cv::waitKey(0);

    return 0;
}
