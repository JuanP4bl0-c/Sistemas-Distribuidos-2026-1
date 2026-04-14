# ==============================
# Configurações gerais
# ==============================
TARGETS = cliente teste

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# ==============================
# Arquivos fonte
# ==============================

# Todos os .cpp do src (modelos, streams, network, utils, etc.)
SRC_FILES = $(shell find $(SRC_DIR) -name "*.cpp")

# Arquivos de teste
TEST_FILES = $(shell find $(TEST_DIR) -name "*.cpp")

# Separando o main do cliente
CLIENT_MAIN = $(SRC_DIR)/main.cpp
CLIENT_SRC = $(filter-out $(CLIENT_MAIN), $(SRC_FILES))

# ==============================
# Objetos
# ==============================

CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRC)) \
             $(OBJ_DIR)/main.o

TEST_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRC)) \
           $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/tests/%.o,$(TEST_FILES))

# ==============================
# Regra principal
# ==============================

all: $(TARGETS)

# ==============================
# Executável: cliente
# ==============================

cliente: $(CLIENT_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@

# ==============================
# Executável: teste
# ==============================

teste: $(TEST_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@

# ==============================
# Compilação genérica dos objetos
# ==============================

# Para arquivos do src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Para arquivos de teste
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==============================
# Limpeza
# ==============================

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# ==============================
# Execução rápida
# ==============================

run: cliente
	./$(BIN_DIR)/cliente

run_test: teste
	./$(BIN_DIR)/teste

.PHONY: all clean run run_test