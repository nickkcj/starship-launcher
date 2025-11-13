// Nick J - Implementação do renderizador

#include "renderer.h"
#include "../entities/bateria.h"
#include "../entities/nave.h"
#include "../entities/foguete.h"
#include <cmath>

// Função auxiliar para desenhar círculo (SDL2 não tem nativa)
void desenharCirculo(SDL_Renderer* renderer, int cx, int cy, int raio, bool preenchido) {
    for(int w = 0; w < raio * 2; w++) {
        for(int h = 0; h < raio * 2; h++) {
            int dx = raio - w;
            int dy = raio - h;
            if((dx*dx + dy*dy) <= (raio * raio)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

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
    if (!estado) return;

    // Desenhar lançadores como círculos no canto superior esquerdo
    int startX = 20;
    int startY = 20;
    int raio = 12;
    int espacamento = 35;

    for(int i = 0; i < estado->numLancadores; i++) {
        int x = startX + (i * espacamento);
        int y = startY;

        if(estado->lancadores[i] == 1) {
            // Lançador carregado - verde
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        } else {
            // Lançador vazio - cinza escuro
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        }

        desenharCirculo(renderer, x, y, raio, true);

        // Borda branca
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Desenhar círculo de borda (simplificado - apenas alguns pontos)
        for(int angle = 0; angle < 360; angle += 10) {
            int px = x + raio * cos(angle * M_PI / 180.0);
            int py = y + raio * sin(angle * M_PI / 180.0);
            SDL_RenderDrawPoint(renderer, px, py);
        }
    }

    // TODO: Adicionar texto mostrando naves abatidas, escaparam, etc
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
