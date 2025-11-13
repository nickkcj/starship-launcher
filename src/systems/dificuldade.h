// PESSOA 3 - Sistema de níveis de dificuldade

#ifndef DIFICULDADE_H
#define DIFICULDADE_H

// Níveis de dificuldade
enum Dificuldade {
    FACIL = 0,
    MEDIO = 1,
    DIFICIL = 2
};

// Parâmetros de dificuldade
struct ParametrosDificuldade {
    int numLancadores;      // Quantidade de lançadores
    int tempoRecarga;       // Tempo de recarga em segundos
    int velocidadeNave;     // Velocidade das naves (pixels/frame)
    int totalNaves;         // Quantidade total de naves
    int intervaloSpawn;     // Intervalo entre spawn de naves (segundos)
};

// Obter parâmetros baseado na dificuldade
ParametrosDificuldade obterParametros(Dificuldade dif);

// Verificar condição de vitória/derrota
bool verificarVitoria(struct EstadoJogo* estado);
bool verificarDerrota(struct EstadoJogo* estado);

#endif
