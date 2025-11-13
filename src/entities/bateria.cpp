// Nick J - Implementação da bateria

#include "bateria.h"
#include <cstdlib>
#include <cmath>

Bateria* criarBateria(int x, int y) {
    Bateria* bat = new Bateria();
    bat->x = x;
    bat->y = y;
    bat->angulo = VERTICAL; // Padrão para vertical

    return bat;
}

void desenharBateria(SDL_Renderer* renderer, Bateria* bat) {
    if (!bat) return;

    // Base simples da bateria (verde)
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_Rect base = {bat->x - 20, bat->y - 8, 40, 8};
    SDL_RenderFillRect(renderer, &base);

    // Torre central pequena (cinza escuro)
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    SDL_Rect torre = {bat->x - 6, bat->y - 14, 12, 6};
    SDL_RenderFillRect(renderer, &torre);

    // Calcular posição do canhão
    int canX = bat->x;
    int canY = bat->y - 11;

    // Calcular ponta do canhão baseado no ângulo
    int pontaX = canX;
    int pontaY = canY;

    switch(bat->angulo) {
        case VERTICAL:
            pontaX = canX;
            pontaY = canY - 30;
            break;
        case DIAGONAL_ESQ:
            pontaX = canX - 25;
            pontaY = canY - 25;
            break;
        case DIAGONAL_DIR:
            pontaX = canX + 25;
            pontaY = canY - 25;
            break;
        case HORIZONTAL_ESQ:
            pontaX = canX - 30;
            pontaY = canY;
            break;
        case HORIZONTAL_DIR:
            pontaX = canX + 30;
            pontaY = canY;
            break;
    }

    // Desenhar canhão grosso (3 linhas paralelas)
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);

    // Offset perpendicular ao canhão
    float dx = pontaX - canX;
    float dy = pontaY - canY;
    float comprimento = sqrt(dx*dx + dy*dy);
    float perpX = -dy / comprimento * 2;
    float perpY = dx / comprimento * 2;

    // 3 linhas paralelas para dar espessura
    SDL_RenderDrawLine(renderer, canX, canY, pontaX, pontaY);
    SDL_RenderDrawLine(renderer,
        canX + perpX, canY + perpY,
        pontaX + perpX, pontaY + perpY);
    SDL_RenderDrawLine(renderer,
        canX - perpX, canY - perpY,
        pontaX - perpX, pontaY - perpY);
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
