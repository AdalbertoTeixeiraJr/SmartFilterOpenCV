CPP_FLAGS=
OPENCV_LIBS=-lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
BOOST_LIBS=-lboost_system
LD_FLAGS=$(OPENCV_LIBS) $(BOOST_LIBS)

sources=$(wildcard src/*.cpp) # create a list to match with the regular expression
objects=$(patsubst src/%.cpp,release/%.o,$(sources)) # create the .o versions for each one in objects, replace % 

release/%.o: src/%.cpp # $^: left side; $@: right side
	g++ $(CPP_FLAGS) -c $^ -o $@

default: $(objects)
	g++ $(CPP_FLAGS) -o smart_filter $(objects) $(LD_FLAGS)

clean:
	rm -rf release/* smart_filter
