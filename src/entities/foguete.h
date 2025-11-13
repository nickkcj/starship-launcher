// PESSOA 1 - Foguetes

#ifndef FOGUETE_H
#define FOGUETE_H

#include <SDL.h>
#include <pthread.h>
#include "bateria.h"

struct Foguete {
    int x, y;              // Posição atual
    int velocidade;        // Pixels por frame
    AnguloDisparo angulo;  // Direção do foguete
    bool ativo;            // false quando sai da tela

    pthread_t thread;      // Thread que move este foguete
};

// Forward declaration
struct EstadoJogo;

// Funções de foguete
Foguete* criarFoguete(int x, int y, AnguloDisparo angulo);
void desenharFoguete(SDL_Renderer* renderer, Foguete* fog);
void* threadFoguete(void* arg);  // Thread que move o foguete
void destruirFoguete(Foguete* fog);

#endif
