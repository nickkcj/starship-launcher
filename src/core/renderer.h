// Nick J - Sistema de renderização (desenhar na tela)

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "game.h"

// Funções de renderização
void desenharCenario(SDL_Renderer* renderer);
void desenharHUD(SDL_Renderer* renderer, EstadoJogo* estado);
void renderizarTudo(SDL_Renderer* renderer, EstadoJogo* estado);

// Funções auxiliares de desenho
void desenharTexto(SDL_Renderer* renderer, const char* texto, int x, int y);

#endif
