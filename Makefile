CXX=g++
CXXFLAGS= -std=c++11
EXE_SRC_1  := main_ll.cpp
EXE_SRC_2  := main_bt.cpp
TEST_SRC   := test.cpp catch/catchmain.cpp

EXE_OBJ_1  := $(patsubst %.cpp, %.o, $(EXE_SRC_1))
EXE_OBJ_2  := $(patsubst %.cpp, %.o, $(EXE_SRC_2))
EXE_DEP_1  := $(patsubst %.cpp, %.d, $(EXE_SRC_1))
EXE_DEP_2  := $(patsubst %.cpp, %.d, $(EXE_SRC_2))
TEST_OBJ   := $(patsubst %.cpp, %.o, $(TEST_SRC))
TEST_DEP   := $(patsubst %.cpp, %.d, $(TEST_SRC))

WARNING := -Wall -Wextra

all: main_ll main_bt

clean:
	$(RM) $(EXE_OBJ_1) $(EXE_OBJ_2) $(TEST_OBJ) $(EXE_DEP_1) $(EXE_DEP_2) $(TEST_DEP) main_ll main_bt test

#This provides the rule for the executable depending on all the object files
main_ll: $(EXE_OBJ_1)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

main_bt: $(EXE_OBJ_2)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

test: $(TEST_OBJ)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

-include $(EXE_DEP_1) $(EXE_DEP_2)
-include $(TEST_DEP)

#Generic rule to convert individual source file into object file
#-MMD=generates the dependency file %.d which holds the dependency of the
#generated %.o files from corresponding source and header files.
#-MP=adds dummy rules should header files be removed from the file system
%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@
