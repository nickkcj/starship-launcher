// Nick J - Bateria antiaérea

#ifndef BATERIA_H
#define BATERIA_H

#include <SDL.h>

// Ângulos possíveis da bateria
enum AnguloDisparo {
    VERTICAL = 0,      // 90° |
    DIAGONAL_ESQ = 1,  // 45° \
    DIAGONAL_DIR = 2,  // 45° /
    HORIZONTAL_ESQ = 3,// 180° __
    HORIZONTAL_DIR = 4 // 180° __
};

struct Bateria {
    int x;               // Posição X (centro da tela)
    int y;               // Posição Y (perto do fundo)
    AnguloDisparo angulo; // Ângulo atual

    // TODO: Adicionar mais campos se necessário
};

// Funções da bateria
Bateria* criarBateria(int x, int y);
void desenharBateria(SDL_Renderer* renderer, Bateria* bat);
void mudarAngulo(Bateria* bat, AnguloDisparo novoAngulo);
void destruirBateria(Bateria* bat);

#endif
