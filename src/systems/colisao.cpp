// Nick J - Implementação de colisão

#include "colisao.h"
#include "../core/game.h"
#include <cmath>

bool verificarColisao(Foguete* fog, Nave* nave) {
    // Verificar se foguete está próximo da nave usando distância euclidiana
    int dx = fog->x - nave->x;
    int dy = fog->y - nave->y;
    float distancia = sqrt(dx*dx + dy*dy);

    // Raio de colisão: 20 pixels
    return distancia < 20.0f;
}

void verificarTodasColisoes(EstadoJogo* estado) {
    // Verificar colisões entre todos foguetes e naves
    // IMPORTANTE: Usar mutex para acessar listas compartilhadas!

    pthread_mutex_lock(&estado->mutexGeral);

    // Para cada foguete ativo
    for(auto fog : estado->foguetes) {
        if(!fog->ativo) continue;

        // Verificar contra todas as naves ativas
        for(auto nave : estado->naves) {
            if(!nave->ativa) continue;

            // Se colidiu
            if(verificarColisao(fog, nave)) {
                // Desativar ambos
                fog->ativo = false;
                nave->ativa = false;

                // Incrementar contador
                estado->navesAbatidas++;

                // Um foguete só pode acertar uma nave
                break;
            }
        }
    }

    pthread_mutex_unlock(&estado->mutexGeral);
}
