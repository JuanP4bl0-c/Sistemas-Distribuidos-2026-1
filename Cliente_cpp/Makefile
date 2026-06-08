# ==============================
# Configurações gerais
# ==============================
TARGET = bin/cliente
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -lcurl 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# ==============================
# Ficheiros fonte
# ==============================
# Busca todos os arquivos .cpp recursivamente em src/
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Converte arquivos .cpp em .o na pasta obj/
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# ==============================
# Regra principal
# ==============================
all: $(TARGET)

# ==============================
# Executável
# ==============================
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "✅ Executável '$(TARGET)' gerado com sucesso."

# ==============================
# Compilação dos objetos
# ==============================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==============================
# Comandos úteis
# ==============================
run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "🧹 Pastas bin/ e obj/ limpas."

.PHONY: all clean run