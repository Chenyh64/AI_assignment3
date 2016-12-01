OPENCV_INCLUDE_PATH=~/opencv/release/include
OPENCV_LIB_PATH=~/opencv/release/lib
USED_LIB=-lopencv_core -lopencv_highgui -lopencv_imgproc

all: dir map_gen seq_gen
dir:
	mkdir bin
map_gen: map_gen.cpp map_maker.h map_maker.cpp
	g++ -g map_gen.cpp map_maker.h map_maker.cpp -I$(OPENCV_INCLUDE_PATH) -L$(OPENCV_LIB_PATH) $(USED_LIB) -o bin/map_gen

seq_gen: seq_gen.cpp rob_seq.h rob_seq.cpp map_maker.h map_maker.cpp
	g++ -g seq_gen.cpp rob_seq.h rob_seq.cpp map_maker.h map_maker.cpp -I$(OPENCV_INCLUDE_PATH) -L$(OPENCV_LIB_PATH) $(USED_LIB) -o bin/seq_gen

clean:
	rm -rf bin
