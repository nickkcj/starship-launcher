# Makefile para o jogo de defesa antiaérea
# Uso: make       -> compila o jogo
#      make run   -> compila e executa
#      make clean -> remove executável

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
SDL_FLAGS = $(shell sdl2-config --cflags --libs)

# Arquivos
SRC = src/main.cpp
TARGET = antiaerea

# Regra principal
all: $(TARGET)

# Compilar o jogo
$(TARGET): $(SRC)
	@echo "Compilando..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SDL_FLAGS)
	@echo "✓ Compilado com sucesso!"

# Compilar e executar
run: $(TARGET)
	@echo "Executando..."
	./$(TARGET)

# Limpar
clean:
	@echo "Limpando..."
	rm -f $(TARGET)
	@echo "✓ Limpo!"

.PHONY: all run clean
