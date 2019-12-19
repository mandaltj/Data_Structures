EXE_SRC  := main.cpp
TEST_SRC := test.cpp catch/catchmain.cpp

EXE_OBJ  := $(patsubst %.cpp, %.o, $(EXE_SRC))
TEST_OBJ := $(patsubst %.cpp, %.o, $(TEST_SRC))
EXE_DEP  := $(patsubst %.cpp, %.d, $(EXE_SRC))
TEST_DEP := $(patsubst %.cpp, %.d, $(TEST_SRC))

WARNING := -Wall -Wextra

all: main

clean:
	$(RM) $(EXE_OBJ) $(TEST_OBJ) $(EXE_DEP) $(TEST_DEP) main test

#This provides the rule for the executable depending on all the object files
main: $(EXE_OBJ)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

test: $(TEST_OBJ)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

-include $(EXE_DEP)
-include $(TEST_DEP)

#Generic rule to convert individual source file into object file
#-MMD=generates the dependency file %.d which holds the dependency of the
#generated %.o files from corresponding source and header files.
#-MP=adds dummy rules should header files be removed from the file system
%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@
