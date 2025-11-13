// PESSOA 1 - Implementação dos foguetes

#include "foguete.h"
#include "../core/game.h"
#include <unistd.h>

Foguete* criarFoguete(int x, int y, AnguloDisparo angulo) {
    // TODO: Criar foguete
    // - Alocar memória
    // - Inicializar posição, ângulo, velocidade
    // - Marcar como ativo
    // - NÃO criar thread aqui (main.cpp faz isso)

    return nullptr; // SUBSTITUIR
}

void desenharFoguete(SDL_Renderer* renderer, Foguete* fog) {
    // TODO: Desenhar foguete como um pequeno retângulo ou círculo
    // Exemplo:
    // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Amarelo
    // SDL_Rect rect = {fog->x - 2, fog->y - 2, 4, 4};
    // SDL_RenderFillRect(renderer, &rect);
}

void* threadFoguete(void* arg) {
    // TODO: Thread que move o foguete continuamente
    // 1. Receber ponteiro para EstadoJogo
    // 2. Loop enquanto foguete ativo:
    //    - Atualizar posição baseado no ângulo
    //    - Verificar se saiu da tela (marcar inativo)
    //    - Dormir um pouco (usleep)
    // 3. Retornar

    // Dica: movimento baseado no ângulo:
    // VERTICAL: y diminui
    // DIAGONAL_ESQ: y diminui, x diminui
    // DIAGONAL_DIR: y diminui, x aumenta
    // HORIZONTAL_ESQ: x diminui
    // HORIZONTAL_DIR: x aumenta

    return nullptr;
}

void destruirFoguete(Foguete* fog) {
    // TODO: Liberar memória
    // delete fog;
}
