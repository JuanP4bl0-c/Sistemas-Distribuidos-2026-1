# ==============================
# Configurações gerais
# ==============================
TARGETS = cliente teste

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = 

SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# ==============================
# Arquivos fonte
# ==============================

# Todos os .cpp do src (inclui modelos, streams, network, utils e protocols)
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Arquivos de teste
TEST_FILES = $(shell find $(TEST_DIR) -type f -name "*.cpp")

# Separando o main do cliente
CLIENT_MAIN = $(SRC_DIR)/main.cpp
CLIENT_SRC  = $(filter-out $(CLIENT_MAIN), $(SRC_FILES))

# ==============================
# Objetos
# ==============================

# Objetos do cliente
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRC)) \
             $(OBJ_DIR)/main.o

# Objetos dos testes
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
	$(CXX) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)
	@echo "Executável 'cliente' gerado em $(BIN_DIR)/cliente"

# ==============================
# Executável: teste
# ==============================

teste: $(TEST_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)
	@echo "Executável 'teste' gerado em $(BIN_DIR)/teste"

# ==============================
# Compilação genérica dos objetos
# ==============================

# Para arquivos do src (inclui protocols automaticamente)
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

# ==============================
# Ajuda
# ==============================

help:
	@echo "Comandos disponíveis:"
	@echo "  make            - Compila cliente e testes"
	@echo "  make cliente    - Compila apenas o cliente"
	@echo "  make teste      - Compila apenas os testes"
	@echo "  make run        - Executa o cliente"
	@echo "  make run_test   - Executa os testes"
	@echo "  make clean      - Remove arquivos compilados"

.PHONY: all clean run run_test help
