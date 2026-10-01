CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude
OUT_DIR := output
APP := $(OUT_DIR)/CPU.exe
TEST := $(OUT_DIR)/CPU_tests.exe
LIB_SRCS := $(filter-out src/main.cpp, $(wildcard src/*.cpp))
APP_SRCS := src/main.cpp $(LIB_SRCS)
TEST_SRCS := tests/cpu_tests.cpp $(LIB_SRCS)

.PHONY: all build run test clean

all: build

build: $(APP)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

$(APP): $(APP_SRCS) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(APP_SRCS) -o $(APP)

$(TEST): $(TEST_SRCS) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST)

run: $(APP)
	./$(APP)

test: $(TEST)
	./$(TEST)

clean:
	rm -rf $(OUT_DIR)
