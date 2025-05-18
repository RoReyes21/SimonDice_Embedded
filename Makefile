CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23 -O2
LD_FLAGS := -lwiringPi -lrpidisplaygl -llgpio

TARGET := SimonDice

SRC_DIR := src
OBJ_DIR := obj

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LD_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_display: CXXFLAGS += -DTEST_DISPLAY
test_display: all

test_controller: CXXFLAGS += -DTEST_CONTROLLER
test_controller: all

test_simon: CXXFLAGS += -DTEST_SIMON_DICE
test_simon: all

clean:
	rm -f $(TARGET) $(OBJ)
	rm -rf $(OBJ_DIR)