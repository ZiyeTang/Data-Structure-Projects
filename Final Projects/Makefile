# Executable names:
EXE = netflix
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o graph.o BFS.o # Point.o FloodFilledImage.o Animation.o


main.o: main.cpp
graph.o: graph.h graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp
# mp_traverals specific stuff
# Add all `colorPicker` and `imageTraversal`s:
# CPP_FILES += $(wildcard colorPicker/*.cpp)
# CPP_FILES += $(wildcard imageTraversal/*.cpp)
# OBJS += $(CPP_FILES:.cpp=.o)

# Generated files
# CLEAN_RM = 

# Use the cs225 makefile template:
include cs225/make/cs225.mk