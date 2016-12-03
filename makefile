OPENCV_INCLUDE_PATH=~/opencv/release/include
OPENCV_LIB_PATH=~/opencv/release/lib
USED_LIB=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_contrib
SEQ_GEN_FILE= seq_gen.cpp map_maker.h map_maker.cpp filtering_solver.h filtering_solver.cpp probability_map.h probability_map.cpp transition_model.h transition_model.cpp sensor_model.h sensor_model.cpp rob_seq.h rob_seq.cpp
FTEST_FILE=filterTest.cpp map_maker.h map_maker.cpp filtering_solver.h filtering_solver.cpp probability_map.h probability_map.cpp transition_model.h transition_model.cpp sensor_model.h sensor_model.cpp rob_seq.h rob_seq.cpp

all: dir map_gen seq_gen fTest
dir:
	mkdir bin
map_gen: map_gen.cpp map_maker.h map_maker.cpp
	g++ -g map_gen.cpp map_maker.h map_maker.cpp -I$(OPENCV_INCLUDE_PATH) -L$(OPENCV_LIB_PATH) $(USED_LIB) -o bin/map_gen

seq_gen: $(SEQ_GEN_FILE)
	g++ -g $(SEQ_GEN_FILE) -I$(OPENCV_INCLUDE_PATH) -L$(OPENCV_LIB_PATH) $(USED_LIB) -o bin/seq_gen

fTest: $(FTEST_FILE)
	g++ -g $(FTEST_FILE) -I$(OPENCV_INCLUDE_PATH) -L$(OPENCV_LIB_PATH) $(USED_LIB) -o bin/fTest

clean:
	rm -rf bin
