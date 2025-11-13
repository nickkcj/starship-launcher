// PESSOA 1 - Implementação do estado do jogo

#include "game.h"
#include "../entities/bateria.h"
#include "../entities/nave.h"
#include "../entities/foguete.h"
#include <cstdlib>

void inicializarJogo(EstadoJogo* estado, int dificuldade) {
    // TODO: Inicializar todos os campos do EstadoJogo
    // - Criar bateria
    // - Configurar lançadores baseado na dificuldade
    // - Inicializar mutexes e condition variables
    // - Resetar contadores

    // Exemplo:
    // pthread_mutex_init(&estado->mutexGeral, nullptr);
    // pthread_mutex_init(&estado->mutexLancadores, nullptr);
    // pthread_cond_init(&estado->condCarregador, nullptr);
}

void finalizarJogo(EstadoJogo* estado) {
    // TODO: Limpar recursos
    // - Destruir mutexes
    // - Liberar memória de naves e foguetes
    // - Liberar bateria

    // Exemplo:
    // pthread_mutex_destroy(&estado->mutexGeral);
    // pthread_mutex_destroy(&estado->mutexLancadores);
    // pthread_cond_destroy(&estado->condCarregador);
}
