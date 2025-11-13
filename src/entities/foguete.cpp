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

    // Calcular direção do míssil baseado no ângulo
    float dirX = 0, dirY = -1; // Padrão: vertical
    switch(fog->angulo) {
        case VERTICAL:
            dirX = 0; dirY = -1;
            break;
        case DIAGONAL_ESQ:
            dirX = -0.707f; dirY = -0.707f;
            break;
        case DIAGONAL_DIR:
            dirX = 0.707f; dirY = -0.707f;
            break;
        case HORIZONTAL_ESQ:
            dirX = -1; dirY = 0;
            break;
        case HORIZONTAL_DIR:
            dirX = 1; dirY = 0;
            break;
    }

    // RASTRO DE FOGO (desenhar primeiro, atrás do míssil)
    for(int i = 0; i < 8; i++) {
        // Partículas atrás do foguete
        int rastroX = fog->x - dirX * (i * 4);
        int rastroY = fog->y - dirY * (i * 4);

        // Cores degradê: amarelo -> laranja -> vermelho -> escuro
        if(i < 2) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255); // Amarelo claro
        } else if(i < 4) {
            SDL_SetRenderDrawColor(renderer, 255, 180, 0, 255); // Laranja
        } else if(i < 6) {
            SDL_SetRenderDrawColor(renderer, 255, 80, 0, 255); // Vermelho
        } else {
            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255); // Vermelho escuro
        }

        // Tamanho diminui conforme se afasta
        int tamanho = 4 - (i / 2);
        if(tamanho < 1) tamanho = 1;
        SDL_Rect particula = {rastroX - tamanho/2, rastroY - tamanho/2, tamanho, tamanho};
        SDL_RenderFillRect(renderer, &particula);
    }

    // CORPO DO MÍSSIL (retângulo branco/amarelo)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect corpo = {fog->x - 3, fog->y - 5, 6, 10};
    SDL_RenderFillRect(renderer, &corpo);

    // Detalhes no corpo (linhas pretas)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderDrawLine(renderer, fog->x - 2, fog->y - 2, fog->x - 2, fog->y + 2);
    SDL_RenderDrawLine(renderer, fog->x + 2, fog->y - 2, fog->x + 2, fog->y + 2);

    // PONTA DO MÍSSIL (triângulo vermelho brilhante)
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    // Aproximação com retângulos para fazer triângulo
    SDL_Rect ponta1 = {fog->x - 2, fog->y - 5, 4, 2};
    SDL_RenderFillRect(renderer, &ponta1);
    SDL_Rect ponta2 = {fog->x - 1, fog->y - 7, 2, 2};
    SDL_RenderFillRect(renderer, &ponta2);
    SDL_Rect ponta3 = {fog->x, fog->y - 8, 1, 1};
    SDL_RenderFillRect(renderer, &ponta3);

    // ALETAS (cinza, na base)
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    // Aleta esquerda
    SDL_Rect aletaE = {fog->x - 5, fog->y + 3, 2, 4};
    SDL_RenderFillRect(renderer, &aletaE);
    // Aleta direita
    SDL_Rect aletaD = {fog->x + 3, fog->y + 3, 2, 4};
    SDL_RenderFillRect(renderer, &aletaD);

    // Brilho no corpo (linha branca brilhante)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, fog->x, fog->y - 4, fog->x, fog->y + 3);
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
