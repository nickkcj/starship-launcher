// Nick D - Naves alienígenas

#ifndef NAVE_H
#define NAVE_H

#include <SDL.h>
#include <SDL_image.h>
#include <pthread.h>

struct Nave {
    int x, y;           // Posição atual
    int velocidade;     // Pixels por frame (baseado na dificuldade)
    bool ativa;         // false quando abatida ou chegou no chão

    pthread_t thread;   // Thread que move esta nave

    // Textura PNG (Nick D vai carregar a imagem aqui)
    SDL_Texture* textura;
};

// Forward declaration
struct EstadoJogo;

// Funções de nave
Nave* criarNave(int x, int velocidade);
void desenharNave(SDL_Renderer* renderer, Nave* nave);
void* threadNave(void* arg);        // Thread que move a nave
void* threadSpawnNaves(void* arg);  // Thread que cria naves periodicamente
void destruirNave(Nave* nave);

// Função auxiliar para carregar PNG (Nick D implementa)
SDL_Texture* carregarTexturaNave(SDL_Renderer* renderer, const char* caminhoImagem);

#endif
