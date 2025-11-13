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

    // Desenhar foguete como pequeno retângulo amarelo
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect rect = {fog->x - 3, fog->y - 3, 6, 6};
    SDL_RenderFillRect(renderer, &rect);

    // Borda vermelha para destaque
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
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
