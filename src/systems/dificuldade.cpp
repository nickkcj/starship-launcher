// Nick C - Implementação de dificuldade

#include "dificuldade.h"
#include "../core/game.h"

ParametrosDificuldade obterParametros(Dificuldade dif) {
    ParametrosDificuldade params;

    switch(dif) {
        case FACIL:
            params.numLancadores = 2;
            params.tempoRecarga = 3;
            params.velocidadeNave = 1;
            params.totalNaves = 10;
            params.intervaloSpawn = 3;
            break;

        case MEDIO:
            params.numLancadores = 3;
            params.tempoRecarga = 2;
            params.velocidadeNave = 2;
            params.totalNaves = 15;
            params.intervaloSpawn = 2;
            break;

        case DIFICIL:
            params.numLancadores = 5;
            params.tempoRecarga = 1;
            params.velocidadeNave = 3;
            params.totalNaves = 20;
            params.intervaloSpawn = 1;
            break;
    }

    return params;
}

bool verificarVitoria(EstadoJogo* estado) {
    return estado->navesAbatidas >= (estado->totalNaves / 2);
}

bool verificarDerrota(EstadoJogo* estado) {
    return estado->navesEscaparam > (estado->totalNaves / 2);
}
