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
	@echo "├── main.cpp              [Nick J] Loop principal"
	@echo "├── main_completo.cpp     [Nick J] Versão final"
	@echo "├── core/"
	@echo "│   ├── game.h/cpp        [Nick J] Estado global"
	@echo "│   └── renderer.h/cpp    [Nick J] Renderização"
	@echo "├── entities/"
	@echo "│   ├── bateria.h/cpp     [Nick J] Bateria"
	@echo "│   ├── nave.h/cpp        [Nick D] Naves"
	@echo "│   └── foguete.h/cpp     [Nick J] Foguetes"
	@echo "└── systems/"
	@echo "    ├── colisao.h/cpp     [Nick J] Colisão"
	@echo "    ├── carregador.h/cpp  [Nick C] Carregador"
	@echo "    └── dificuldade.h/cpp [Nick C] Dificuldade"
	@echo ""
	@echo "Nick J (50%): core/, bateria, foguete, colisao + integração"
	@echo "Nick D (25%): nave + relatório"
	@echo "Nick C (25%): carregador, dificuldade + relatório"

.PHONY: all run clean info full
