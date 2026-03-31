TARGETS = cliente teste

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_MODEL = $(wildcard src/modelos/*.cpp)
SRC_STREAMS = $(wildcard src/streams/*.cpp)

OBJ_DIR = obj
BIN_DIR = bin

OBJ_MODEL = $(patsubst src/modelos/%.cpp,$(OBJ_DIR)/%.o,$(SRC_MODEL))
OBJ_STREAMS = $(patsubst src/streams/%.cpp,$(OBJ_DIR)/%.o,$(SRC_STREAMS))

all: $(TARGETS)

# regra para cliente
cliente: $(OBJ_MODEL) $(OBJ_STREAMS) $(OBJ_DIR)/cliente.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@

# regra para teste
teste: $(OBJ_MODEL) $(OBJ_STREAMS) $(OBJ_DIR)/teste.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@

# regra genérica para objetos
$(OBJ_DIR)/%.o: src/modelos/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/streams/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/app/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean