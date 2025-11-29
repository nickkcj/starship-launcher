// Nick J - Estado global do jogo e sincronização
// Define as estruturas principais e variáveis compartilhadas entre threads

#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <vector>

// Forward declarations (evita includes circulares)
struct Nave;
struct Foguete;
struct Bateria;

// Constantes do jogo
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;
const int NUM_LANCADORES = 3;  // Ajustar por dificuldade

// Estado global do jogo (compartilhado entre threads)
struct EstadoJogo {
    // Bateria
    Bateria* bateria;

    // Lançadores (0 = vazio, 1 = carregado)
    int lancadores[5];  // Máximo 5 lançadores
    int numLancadores;  // Quantidade atual (depende da dificuldade)

    // Listas compartilhadas
    std::vector<Nave*> naves;
    std::vector<Foguete*> foguetes;

    // Contadores
    int navesAbatidas;
    int navesEscaparam;
    int totalNaves;

    // Controle
    bool jogoAtivo;
    bool vitoria;  // true = vitória, false = derrota
    int tempoRecarga;  // Tempo em segundos para recarregar lançadores

    // Sincronização (IMPORTANTE!)
    pthread_mutex_t mutexGeral;           // Protege listas e contadores
    pthread_mutex_t mutexLancadores;      // Protege array de lançadores
    pthread_cond_t condCarregador;        // Sinaliza carregador

    // TODO: Adicionar mais conforme necessário
};

// Funções de inicialização/finalização
void inicializarJogo(EstadoJogo* estado, int dificuldade);
void finalizarJogo(EstadoJogo* estado);

#endif
