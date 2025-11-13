// Nick D - Implementação das naves

#include "nave.h"
#include "../core/game.h"
#include <cstdlib>
#include <unistd.h>

Nave* criarNave(int x, int velocidade) {
    // TODO: Criar nave
    // - Alocar memória
    // - Inicializar x, y=0, velocidade
    // - Marcar como ativa
    // - NÃO criar thread aqui (threadSpawnNaves faz isso)

    return nullptr; // SUBSTITUIR
}

void desenharNave(SDL_Renderer* renderer, Nave* nave) {
    // TODO: Desenhar nave como retângulo ou triângulo
    // Exemplo:
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Vermelho
    // SDL_Rect rect = {nave->x - 10, nave->y - 5, 20, 10};
    // SDL_RenderFillRect(renderer, &rect);
}

void* threadNave(void* arg) {
    // TODO: Thread que move a nave para baixo
    // 1. Receber ponteiro para estrutura com (EstadoJogo*, Nave*)
    // 2. Loop enquanto nave ativa:
    //    - Aumentar y (descer)
    //    - Verificar se chegou no chão (y > ALTURA_TELA - 50)
    //       Se sim: marcar inativa, incrementar navesEscaparam
    //    - Dormir um pouco (usleep)
    // 3. Retornar

    // IMPORTANTE: Usar mutex ao modificar contadores!

    return nullptr;
}

void* threadSpawnNaves(void* arg) {
    // TODO: Thread que cria naves periodicamente
    // 1. Receber EstadoJogo
    // 2. Loop enquanto não criou todas as naves:
    //    - Criar nave em posição X aleatória (rand() % LARGURA_TELA)
    //    - Adicionar na lista (MUTEX!)
    //    - Criar thread para mover a nave
    //    - Dormir um tempo (baseado na dificuldade)
    // 3. Retornar

    // Exemplo:
    // while(estado->naves.size() < estado->totalNaves && estado->jogoAtivo) {
    //     int x = rand() % LARGURA_TELA;
    //     Nave* nova = criarNave(x, velocidade);
    //
    //     pthread_mutex_lock(&estado->mutexGeral);
    //     estado->naves.push_back(nova);
    //     pthread_mutex_unlock(&estado->mutexGeral);
    //
    //     pthread_create(&nova->thread, nullptr, threadNave, ...);
    //     sleep(2);  // Intervalo entre naves
    // }

    return nullptr;
}

void destruirNave(Nave* nave) {
    // TODO: Liberar memória
    // delete nave;
}
