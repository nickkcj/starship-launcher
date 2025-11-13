// PESSOA 3 - Implementação de dificuldade

#include "dificuldade.h"
#include "../core/game.h"

ParametrosDificuldade obterParametros(Dificuldade dif) {
    // TODO: Retornar parâmetros baseado na dificuldade
    // Ajustar valores para balancear o jogo

    ParametrosDificuldade params;

    switch(dif) {
        case FACIL:
            // TODO: Poucos lançadores, recarga lenta, poucas naves lentas
            // params.numLancadores = 2;
            // params.tempoRecarga = 3;  // 3 segundos
            // params.velocidadeNave = 1;
            // params.totalNaves = 10;
            // params.intervaloSpawn = 3;
            break;

        case MEDIO:
            // TODO: Valores medianos
            // params.numLancadores = 3;
            // params.tempoRecarga = 2;
            // params.velocidadeNave = 2;
            // params.totalNaves = 15;
            // params.intervaloSpawn = 2;
            break;

        case DIFICIL:
            // TODO: Muitos lançadores, recarga rápida, muitas naves rápidas
            // params.numLancadores = 5;
            // params.tempoRecarga = 1;
            // params.velocidadeNave = 3;
            // params.totalNaves = 20;
            // params.intervaloSpawn = 1;
            break;
    }

    return params;
}

bool verificarVitoria(EstadoJogo* estado) {
    // TODO: Verificar se abateu >= 50% das naves
    // return estado->navesAbatidas >= (estado->totalNaves / 2);

    return false; // SUBSTITUIR
}

bool verificarDerrota(EstadoJogo* estado) {
    // TODO: Verificar se > 50% das naves escaparam
    // return estado->navesEscaparam > (estado->totalNaves / 2);

    return false; // SUBSTITUIR
}
