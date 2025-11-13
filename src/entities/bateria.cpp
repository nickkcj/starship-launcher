// Nick J - Implementação da bateria

#include "bateria.h"
#include <cstdlib>

Bateria* criarBateria(int x, int y) {
    Bateria* bat = new Bateria();
    bat->x = x;
    bat->y = y;
    bat->angulo = VERTICAL; // Padrão para vertical

    return bat;
}

void desenharBateria(SDL_Renderer* renderer, Bateria* bat) {
    if (!bat) return;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect base = {bat->x - 20, bat->y - 10, 40, 10};
    SDL_RenderFillRect(renderer, &base);

    // Canhão (muda com base no angulo)
    switch(bat->angulo) {
          case VERTICAL:
              SDL_RenderDrawLine(renderer,
  bat->x, bat->y, bat->x, bat->y - 30);
              break;
          case DIAGONAL_ESQ:
              SDL_RenderDrawLine(renderer,
  bat->x, bat->y, bat->x - 20, bat->y - 20);
              break;
          case DIAGONAL_DIR:
              SDL_RenderDrawLine(renderer,
  bat->x, bat->y, bat->x + 20, bat->y - 20);
              break;
          case HORIZONTAL_ESQ:
              SDL_RenderDrawLine(renderer,
  bat->x, bat->y, bat->x - 30, bat->y);
              break;
          case HORIZONTAL_DIR:
              SDL_RenderDrawLine(renderer,
  bat->x, bat->y, bat->x + 30, bat->y);
              break;
      }
  }


void mudarAngulo(Bateria* bat, AnguloDisparo novoAngulo) {
    if (bat) {
        bat->angulo = novoAngulo;
    }
}

void destruirBateria(Bateria* bat) {
    if (bat) {
        delete bat;
    }
}
