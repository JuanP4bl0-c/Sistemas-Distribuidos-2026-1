# Nome do executável
TARGET = cliente

# Compilador
CXX = g++

# Flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Objetos
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Executável final
EXEC = $(BIN_DIR)/$(TARGET)

# Regra principal
all: $(EXEC)

# Linkagem
$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $(EXEC)

# Compilação
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Executar
run: all
	./$(EXEC)

# Debug (extra 🔥)
debug: CXXFLAGS += -g
debug: clean all

.PHONY: all clean run debug