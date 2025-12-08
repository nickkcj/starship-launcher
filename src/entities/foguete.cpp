// Nick J - Implementação dos foguetes

#include "foguete.h"
#include "../core/game.h"
#include <unistd.h>

// Estrutura para passar dados para thread do foguete
struct DadosFoguete {
    Foguete* foguete;
    EstadoJogo* estado;
};

Foguete* criarFoguete(int x, int y, AnguloDisparo angulo) {
    Foguete* fog = new Foguete;
    fog->x = x;
    fog->y = y;
    fog->angulo = angulo;
    fog->velocidade = 8;  // Pixels por frame
    fog->ativo = true;

    return fog;
}

void desenharFoguete(SDL_Renderer* renderer, Foguete* fog) {
    if (!fog || !fog->ativo) return;

    // Direção do foguete (para onde está indo)
    float dirX = 0, dirY = -1;
    switch(fog->angulo) {
        case VERTICAL:      dirX = 0;      dirY = -1;     break;
        case DIAGONAL_ESQ:  dirX = -0.707f; dirY = -0.707f; break;
        case DIAGONAL_DIR:  dirX = 0.707f;  dirY = -0.707f; break;
        case HORIZONTAL_ESQ: dirX = -1;     dirY = 0;      break;
        case HORIZONTAL_DIR: dirX = 1;      dirY = 0;      break;
    }

    // Perpendicular (para desenhar espessura)
    float perpX = -dirY;
    float perpY = dirX;

    // RASTRO DE FOGO
    for(int i = 0; i < 8; i++) {
        int rastroX = fog->x - dirX * (i * 4);
        int rastroY = fog->y - dirY * (i * 4);

        // Degradê de cores
        int r = 255, g = 255 - i * 25, b = 100 - i * 12;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        int tamanho = 4 - (i / 2);
        if (tamanho < 1) tamanho = 1;
        SDL_Rect particula = {rastroX - tamanho/2, rastroY - tamanho/2, tamanho, tamanho};
        SDL_RenderFillRect(renderer, &particula);
    }

    // CORPO DO MÍSSIL (linha grossa na direção do movimento)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int x1 = fog->x - dirX * 5;
    int y1 = fog->y - dirY * 5;
    int x2 = fog->x + dirX * 5;
    int y2 = fog->y + dirY * 5;

    // Desenhar corpo com espessura
    for (int i = -2; i <= 2; i++) {
        SDL_RenderDrawLine(renderer,
            x1 + perpX * i, y1 + perpY * i,
            x2 + perpX * i, y2 + perpY * i);
    }

    // PONTA DO MÍSSIL (na direção do movimento)
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    int pontaX = fog->x + dirX * 8;
    int pontaY = fog->y + dirY * 8;
    for (int i = -1; i <= 1; i++) {
        SDL_RenderDrawLine(renderer,
            fog->x + dirX * 5 + perpX * i * 2, fog->y + dirY * 5 + perpY * i * 2,
            pontaX, pontaY);
    }

    // ALETAS (perpendiculares ao corpo, na traseira)
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    int traX = fog->x - dirX * 5;
    int traY = fog->y - dirY * 5;
    // Aleta 1
    SDL_RenderDrawLine(renderer, traX, traY, traX + perpX * 5, traY + perpY * 5);
    // Aleta 2
    SDL_RenderDrawLine(renderer, traX, traY, traX - perpX * 5, traY - perpY * 5);
}

void* threadFoguete(void* arg) {
    DadosFoguete* dados = (DadosFoguete*)arg;
    Foguete* fog = dados->foguete;
    EstadoJogo* estado = dados->estado;

    while (fog->ativo && estado->jogoAtivo) {
        // Atualizar posição baseado no ângulo
        switch(fog->angulo) {
            case VERTICAL:
                fog->y -= fog->velocidade;  // Sobe
                break;
            case DIAGONAL_ESQ:
                fog->y -= fog->velocidade * 0.7;  // Sobe e vai pra esquerda
                fog->x -= fog->velocidade * 0.7;
                break;
            case DIAGONAL_DIR:
                fog->y -= fog->velocidade * 0.7;  // Sobe e vai pra direita
                fog->x += fog->velocidade * 0.7;
                break;
            case HORIZONTAL_ESQ:
                fog->x -= fog->velocidade;  // Vai pra esquerda
                break;
            case HORIZONTAL_DIR:
                fog->x += fog->velocidade;  // Vai pra direita
                break;
        }

        // Verificar se saiu da tela
        if (fog->y < -10 || fog->y > ALTURA_TELA + 10 ||
            fog->x < -10 || fog->x > LARGURA_TELA + 10) {
            fog->ativo = false;
        }

        // ~60 FPS
        usleep(16667);  // ~16ms
    }

    delete dados;  // Liberar dados passados para thread
    return nullptr;
}

void destruirFoguete(Foguete* fog) {
    if (fog) {
        delete fog;
    }
}
