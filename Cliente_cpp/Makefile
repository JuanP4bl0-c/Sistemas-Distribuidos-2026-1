CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g3 -Iinclude
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
OUT_DIR = output

SOURCES = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(OBJ_DIR)/main.o $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp))
TARGET = $(OUT_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build concluido: $@"

$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Limpeza concluida"

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

.PHONY: all clean run rebuild