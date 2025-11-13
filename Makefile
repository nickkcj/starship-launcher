# Makefile para o jogo de defesa antiaérea
# Uso: make       -> compila o hello world atual (para testar)
#      make full  -> compila o jogo completo (quando implementado)
#      make run   -> compila e executa
#      make clean -> remove executáveis

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
SDL_FLAGS = $(shell sdl2-config --cflags --libs)

# Arquivos
SRC_HELLO = src/main.cpp
SRC_FULL = src/core/game.cpp src/core/renderer.cpp \
           src/entities/bateria.cpp src/entities/nave.cpp src/entities/foguete.cpp \
           src/systems/colisao.cpp src/systems/carregador.cpp src/systems/dificuldade.cpp \
           src/main_completo.cpp

TARGET = antiaerea

# Regra padrão: compila hello world simples (para testar SDL2)
all: $(TARGET)

# Compilar hello world (atual)
$(TARGET): $(SRC_HELLO)
	@echo "Compilando hello world..."
	$(CXX) $(CXXFLAGS) $(SRC_HELLO) -o $(TARGET) $(SDL_FLAGS)
	@echo "✓ Compilado! Execute com: ./$(TARGET)"

# Compilar jogo completo (quando implementado)
# DESCOMENTE quando todos os TODOs estiverem prontos
# full:
# 	@echo "Compilando jogo completo..."
# 	$(CXX) $(CXXFLAGS) $(SRC_FULL) -o $(TARGET) $(SDL_FLAGS)
# 	@echo "✓ Jogo completo compilado!"

# Compilar e executar
run: $(TARGET)
	@echo "Executando..."
	./$(TARGET)

# Limpar
clean:
	@echo "Limpando..."
	rm -f $(TARGET) *.o
	@echo "✓ Limpo!"

# Mostrar estrutura do projeto
info:
	@echo "=== Estrutura do Projeto ==="
	@echo ""
	@echo "src/"
	@echo "├── main.cpp              [P1] Loop principal"
	@echo "├── main_completo.cpp     [P1] Versão final"
	@echo "├── core/"
	@echo "│   ├── game.h/cpp        [P1] Estado global"
	@echo "│   └── renderer.h/cpp    [P1] Renderização"
	@echo "├── entities/"
	@echo "│   ├── bateria.h/cpp     [P1] Bateria"
	@echo "│   ├── nave.h/cpp        [P2] Naves"
	@echo "│   └── foguete.h/cpp     [P1] Foguetes"
	@echo "└── systems/"
	@echo "    ├── colisao.h/cpp     [P1] Colisão"
	@echo "    ├── carregador.h/cpp  [P3] Carregador"
	@echo "    └── dificuldade.h/cpp [P3] Dificuldade"
	@echo ""
	@echo "Pessoa 1 (50%): core/, bateria, foguete, colisao + integração"
	@echo "Pessoa 2 (25%): nave + relatório"
	@echo "Pessoa 3 (25%): carregador, dificuldade + relatório"

.PHONY: all run clean info full
