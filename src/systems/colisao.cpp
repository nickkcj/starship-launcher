// Nick J - Implementação de colisão

#include "colisao.h"
#include "../core/game.h"
#include <cmath>

bool verificarColisao(Foguete* fog, Nave* nave) {
    // TODO: Verificar se foguete está próximo da nave
    // Dica: usar distância euclidiana ou AABB (bounding box)

    // Exemplo com distância:
    // int dx = fog->x - nave->x;
    // int dy = fog->y - nave->y;
    // int distancia = sqrt(dx*dx + dy*dy);
    // return distancia < 15;  // Raio de colisão

    return false; // SUBSTITUIR
}

void verificarTodasColisoes(EstadoJogo* estado) {
    // TODO: Verificar colisões entre todos foguetes e naves
    // IMPORTANTE: Usar mutex para acessar listas!

    // pthread_mutex_lock(&estado->mutexGeral);

    // for(auto fog : estado->foguetes) {
    //     if(!fog->ativo) continue;
    //
    //     for(auto nave : estado->naves) {
    //         if(!nave->ativa) continue;
    //
    //         if(verificarColisao(fog, nave)) {
    //             fog->ativo = false;
    //             nave->ativa = false;
    //             estado->navesAbatidas++;
    //             break;
    //         }
    //     }
    // }

    // pthread_mutex_unlock(&estado->mutexGeral);
}
