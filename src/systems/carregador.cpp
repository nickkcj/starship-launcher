// Nick C - Implementação do carregador

#include "carregador.h"
#include "../core/game.h"
#include <unistd.h>

void* threadCarregador(void* arg) {
    EstadoJogo* estado = (EstadoJogo*)arg;

    while(estado->jogoAtivo) {
        pthread_mutex_lock(&estado->mutexLancadores);

        // Verificar se todos estão carregados
        bool todosCarregados = true;
        for(int i = 0; i < estado->numLancadores; i++) {
            if(estado->lancadores[i] == 0) {
                todosCarregados = false;
                break;
            }
        }

        if(todosCarregados) {
            // Espera até alguém disparar (libera mutex enquanto espera)
            pthread_cond_wait(&estado->condCarregador, &estado->mutexLancadores);
            pthread_mutex_unlock(&estado->mutexLancadores);
            continue;
        }

        // Carregar primeiro lançador vazio
        for(int i = 0; i < estado->numLancadores; i++) {
            if(estado->lancadores[i] == 0) {
                estado->lancadores[i] = 1;
                break;
            }
        }

        pthread_mutex_unlock(&estado->mutexLancadores);

        // Tempo de recarga baseado na dificuldade
        sleep(estado->tempoRecarga);
    }

    return nullptr;
}
