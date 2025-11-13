// PESSOA 1 - Implementação da bateria

#include "bateria.h"
#include <cstdlib>

Bateria* criarBateria(int x, int y) {
    // TODO: Alocar memória para bateria e inicializar campos
    // Exemplo:
    // Bateria* bat = new Bateria;
    // bat->x = x;
    // bat->y = y;
    // bat->angulo = VERTICAL;
    // return bat;

    return nullptr; // SUBSTITUIR
}

void desenharBateria(SDL_Renderer* renderer, Bateria* bat) {
    // TODO: Desenhar bateria na tela baseado no ângulo
    // Dica: usar SDL_RenderDrawLine ou SDL_RenderFillRect
    // Desenhar de forma diferente para cada ângulo

    // Exemplo para vertical:
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    // SDL_RenderDrawLine(renderer, bat->x, bat->y, bat->x, bat->y - 30);
}

void mudarAngulo(Bateria* bat, AnguloDisparo novoAngulo) {
    // TODO: Atualizar o ângulo da bateria
    // bat->angulo = novoAngulo;
}

void destruirBateria(Bateria* bat) {
    // TODO: Liberar memória
    // delete bat;
}
