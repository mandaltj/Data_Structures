CXX=g++
CXXFLAGS= -std=c++11 -g
OBJS_DIR = .objs

EXE_SRC_1  := main_ll.cpp
EXE_SRC_2  := main_bt.cpp
EXE_SRC_3  := main_avl.cpp
EXE_SRC_4  := main_heap.cpp

EXE_OBJ_1  := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(EXE_SRC_1))
EXE_OBJ_2  := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(EXE_SRC_2))
EXE_OBJ_3  := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(EXE_SRC_3))
EXE_OBJ_4  := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(EXE_SRC_4))
EXE_DEP_1  := $(patsubst %.cpp, $(OBJS_DIR)/%.d, $(EXE_SRC_1))
EXE_DEP_2  := $(patsubst %.cpp, $(OBJS_DIR)/%.d, $(EXE_SRC_2))
EXE_DEP_3  := $(patsubst %.cpp, $(OBJS_DIR)/%.d, $(EXE_SRC_3))
EXE_DEP_4  := $(patsubst %.cpp, $(OBJS_DIR)/%.d, $(EXE_SRC_4))
TEST_OBJ   := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(TEST_SRC))
TEST_DEP   := $(patsubst %.cpp, $(OBJS_DIR)/%.d, $(TEST_SRC))

WARNING := -Wall -Wextra

all: main_ll main_bt main_avl main_heap

clean:
	rm -rf $(OBJS_DIR) main_ll main_bt main_avl main_heap

#This provides the rule for the executable depending on all the object files
main_ll: $(EXE_OBJ_1)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

main_bt: $(EXE_OBJ_2)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

main_avl: $(EXE_OBJ_3)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

main_heap: $(EXE_OBJ_4)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

-include $(EXE_DEP_1) $(EXE_DEP_2) $(EXE_DEP_3) $(EXE_DEP_4)
-include $(TEST_DEP)
-include $(OBJS_DIR)/*.d

#Ensure .objs/ exists
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

#Generic rule to convert individual source file into object file
#-MMD=generates the dependency file %.d which holds the dependency of the
#generated %.o files from corresponding source and header files.
#-MP=adds dummy rules should header files be removed from the file system
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@
