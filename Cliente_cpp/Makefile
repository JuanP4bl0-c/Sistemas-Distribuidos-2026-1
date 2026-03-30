CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Arquivos fonte
SOURCES	=	cliente_teste.cpp
EXECUTABLE	=	cliente_tcp

# Alvo padrão
all:	$(EXECUTABLE)

# Compilar
$(EXECUTABLE): $(SOURCES)
	$(CXX)	$(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

# Executar
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Limpar
clean:
	rm -f $(EXECUTABLE) *.o

# Help
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o projeto"
	@echo "  make run      - Compila e executa"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make help     - Mostra esta mensagem"
	
.PHONY: all run clean help