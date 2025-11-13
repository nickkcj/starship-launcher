// Nick J - Implementação do estado do jogo

#include "game.h"
#include "../entities/bateria.h"
#include "../entities/nave.h"
#include "../entities/foguete.h"
#include <cstdlib>

void inicializarJogo(EstadoJogo* estado, int dificuldade) {
    // Inicializar bateria (NULL por enquanto, criamos no main)
    estado->bateria = nullptr;

    // Configurar lançadores (por enquanto 3 fixo, depois ajustamos por dificuldade)
    estado->numLancadores = 3;
    for(int i = 0; i < 5; i++) {
        estado->lancadores[i] = 0;  // Todos vazios no início
    }
    // Para testar, começar com 1 lançador carregado
    estado->lancadores[0] = 1;

    // Resetar contadores
    estado->navesAbatidas = 0;
    estado->navesEscaparam = 0;
    estado->totalNaves = 10;  // Por enquanto fixo

    // Estado do jogo
    estado->jogoAtivo = true;
    estado->vitoria = false;

    // Inicializar mutexes e condition variables
    pthread_mutex_init(&estado->mutexGeral, nullptr);
    pthread_mutex_init(&estado->mutexLancadores, nullptr);
    pthread_cond_init(&estado->condCarregador, nullptr);
}

void finalizarJogo(EstadoJogo* estado) {
    // Destruir mutexes e condition variables
    pthread_mutex_destroy(&estado->mutexGeral);
    pthread_mutex_destroy(&estado->mutexLancadores);
    pthread_cond_destroy(&estado->condCarregador);

    // Limpar listas (naves e foguetes serão adicionados depois)
    // TODO: quando tiver naves e foguetes, liberar memória deles aqui

    // Bateria será destruída no main por enquanto
}
