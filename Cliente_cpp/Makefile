# ==============================
# Configurações gerais
# ==============================
TARGETS = cliente

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Bibliotecas do omniORB exigidas para o Linker
LDFLAGS = -lomniORB4 -lomnithread -lomniDynamic4

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# ==============================
# Arquivos fonte
# ==============================

# Busca tanto os .cpp normais quanto os .cc (Stubs do CORBA)
SRC_FILES = $(shell find $(SRC_DIR) -type f \( -name "*.cpp" -o -name "*.cc" \))

CLIENT_MAIN = $(SRC_DIR)/main.cpp
CLIENT_SRC  = $(filter-out $(CLIENT_MAIN), $(SRC_FILES))

# ==============================
# Objetos
# ==============================

# Transforma .cpp e .cc em .o dinamicamente
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%.o,$(basename $(CLIENT_SRC))) \
             $(OBJ_DIR)/main.o

# ==============================
# Regra principal
# ==============================

all: $(TARGETS)

cliente: $(CLIENT_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)
	@echo "Executável 'cliente' gerado em $(BIN_DIR)/cliente"

# ==============================
# Compilação genérica dos objetos
# ==============================

# Regra para compilar .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar o .cc do CORBA
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==============================
# Limpeza e Execução
# ==============================

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: cliente
	./$(BIN_DIR)/cliente

.PHONY: all clean run