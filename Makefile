INC  = `pkg-config --cflags sdl2`
LIBS = `pkg-config --libs sdl2 SDL2_gfx`

CXX	 = g++
CXXFLAGS = -c -Wall -std=c++11 -ggdb $(INC) -I .
#-DDEBUG

sources = $(wildcard *.cpp *.cc)
objects = $(patsubst %.cc, ../bin/%.o,$(patsubst %.cpp,../bin/%.o, $(sources)))
targets = ../bin/fourmis

all : $(targets)

../bin/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# ../bin/%.o : %.cc
# 	$(CXX) $(CXXFLAGS) $< -o $@

../bin/%.o : %.cpp ../include/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

../bin/%.o : %.cc ../include/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(targets) : $(objects)
	$(CXX) $(LDFLAGS) $^ $(LIBS) -o $@

clean :
	-@rm -f *~ ../bin/*.o $(targets)
