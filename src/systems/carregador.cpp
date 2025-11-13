// PESSOA 3 - Implementação do carregador

#include "carregador.h"
#include "../core/game.h"
#include <unistd.h>

void* threadCarregador(void* arg) {
    // TODO: Thread que carrega lançadores automaticamente
    // Esta é a thread MAIS IMPORTANTE para demonstrar sincronização!

    // 1. Receber EstadoJogo
    // 2. Loop enquanto jogo ativo:
    //    a. Verificar se há lançador vazio
    //    b. Se todos cheios:
    //       - pthread_cond_wait (ESPERA até alguém disparar)
    //    c. Se há vazio:
    //       - Carregar primeiro lançador vazio (lancadores[i] = 1)
    //       - Dormir (tempo de recarga baseado na dificuldade)
    // 3. Retornar

    // IMPORTANTE: Usar mutexLancadores e condCarregador!

    // Estrutura básica:
    // EstadoJogo* estado = (EstadoJogo*)arg;
    //
    // while(estado->jogoAtivo) {
    //     pthread_mutex_lock(&estado->mutexLancadores);
    //
    //     // Verificar se todos cheios
    //     bool todosCarregados = true;
    //     for(int i = 0; i < estado->numLancadores; i++) {
    //         if(estado->lancadores[i] == 0) {
    //             todosCarregados = false;
    //             break;
    //         }
    //     }
    //
    //     if(todosCarregados) {
    //         // ESPERAR até alguém disparar
    //         pthread_cond_wait(&estado->condCarregador, &estado->mutexLancadores);
    //         pthread_mutex_unlock(&estado->mutexLancadores);
    //         continue;
    //     }
    //
    //     // Carregar primeiro vazio
    //     for(int i = 0; i < estado->numLancadores; i++) {
    //         if(estado->lancadores[i] == 0) {
    //             estado->lancadores[i] = 1;
    //             break;
    //         }
    //     }
    //
    //     pthread_mutex_unlock(&estado->mutexLancadores);
    //
    //     // Tempo de recarga (varia por dificuldade)
    //     sleep(2);  // Ajustar baseado em dificuldade
    // }

    return nullptr;
}
