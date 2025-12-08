// Nick J - Implementação do estado do jogo

#include "game.h"
#include "../entities/bateria.h"
#include "../entities/nave.h"
#include "../entities/foguete.h"
#include "../systems/dificuldade.h"
#include <SDL.h>
#include <cstdlib>

void inicializarJogo(EstadoJogo* estado, int dificuldade) {
    // Obter parâmetros baseado na dificuldade
    ParametrosDificuldade params = obterParametros((Dificuldade)dificuldade);

    // Inicializar bateria (NULL por enquanto, criamos no main)
    estado->bateria = nullptr;

    // Configurar lançadores baseado na dificuldade
    estado->numLancadores = params.numLancadores;
    for(int i = 0; i < 5; i++) {
        estado->lancadores[i] = 0;  // Todos vazios no início
    }
    estado->lancadores[0] = 1;  // Começar com 1 carregado

    // Resetar contadores
    estado->navesAbatidas = 0;
    estado->navesEscaparam = 0;
    estado->totalNaves = params.totalNaves;

    // Estado do jogo
    estado->jogoAtivo = true;
    estado->vitoria = false;
    estado->tempoRecarga = params.tempoRecarga;
    estado->velocidadeNave = params.velocidadeNave;
    estado->intervaloSpawn = params.intervaloSpawn;

    // Recursos gráficos (serão definidos no main)
    estado->renderer = nullptr;
    estado->texturaNave = nullptr;

    // Inicializar mutexes e condition variables
    pthread_mutex_init(&estado->mutexGeral, nullptr);
    pthread_mutex_init(&estado->mutexLancadores, nullptr);
    pthread_cond_init(&estado->condCarregador, nullptr);
}

void finalizarJogo(EstadoJogo* estado) {
    // Destruir textura compartilhada da nave
    if (estado->texturaNave) {
        SDL_DestroyTexture(estado->texturaNave);
        estado->texturaNave = nullptr;
    }

    // Destruir mutexes e condition variables
    pthread_mutex_destroy(&estado->mutexGeral);
    pthread_mutex_destroy(&estado->mutexLancadores);
    pthread_cond_destroy(&estado->condCarregador);
}
