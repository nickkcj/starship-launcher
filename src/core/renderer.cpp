// Nick J - Implementação do renderizador

#include "renderer.h"
#include "../entities/bateria.h"
#include "../entities/nave.h"
#include "../entities/foguete.h"

void desenharCenario(SDL_Renderer* renderer) {
    // TODO: Desenhar fundo, chão, céu
    // Exemplo:
    // SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255); // Céu escuro
    // SDL_RenderClear(renderer);

    // Linha do chão
    // SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    // SDL_RenderDrawLine(renderer, 0, ALTURA_TELA - 50, LARGURA_TELA, ALTURA_TELA - 50);
}

void desenharHUD(SDL_Renderer* renderer, EstadoJogo* estado) {
    // TODO: Desenhar informações na tela
    // - Quantidade de foguetes disponíveis
    // - Naves abatidas / total
    // - Naves que escaparam

    // Exemplo: desenhar lançadores como círculos
    // for(int i = 0; i < estado->numLancadores; i++) {
    //     if(estado->lancadores[i] == 1) {
    //         // Desenhar círculo cheio (verde)
    //     } else {
    //         // Desenhar círculo vazio (cinza)
    //     }
    // }
}

void renderizarTudo(SDL_Renderer* renderer, EstadoJogo* estado) {
    // TODO: Desenhar tudo na ordem correta
    // 1. Cenário (fundo)
    // 2. Naves
    // 3. Foguetes
    // 4. Bateria
    // 5. HUD
    // 6. SDL_RenderPresent(renderer);
}

void desenharTexto(SDL_Renderer* renderer, const char* texto, int x, int y) {
    // TODO (opcional): Desenhar texto na tela
    // Por enquanto pode usar retângulos para representar números
    // Ou integrar SDL_ttf para fontes reais
}
