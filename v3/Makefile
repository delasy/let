DIR = build
DEP_DIR = $(DIR)/dep
OBJ_DIR = $(DIR)/obj

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
DEPFLAGS = -MF $(DEP_DIR)/$*.d -MMD -MP -MT $@

SRC_FILES = $(wildcard src/*.cpp)
DEP_FILES = $(SRC_FILES:%.cpp=$(DEP_DIR)/%.d)
OBJ_FILES = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

PROJECT_NAME = let

all: init build

build: $(OBJ_FILES)
	$(CXX) $^ -o $(DIR)/$(PROJECT_NAME)

clean:
	@rm -f $(DEP_FILES) $(OBJ_FILES)

init:
	@mkdir -p $(DIR) $(DEP_DIR)/src $(OBJ_DIR)/src

$(OBJ_DIR)/%.o: %.cpp $(DEP_DIR)/%.d | $(DEP_DIR)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@

$(DEP_FILES):
include $(wildcard $(DEP_FILES))

.PHONY: all clean init
