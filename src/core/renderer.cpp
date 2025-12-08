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

// Desenha um dígito usando segmentos (estilo display 7 segmentos)
void desenharDigito(SDL_Renderer* renderer, int digito, int x, int y, int escala) {
    // Cada dígito é 3 unidades de largura e 5 de altura
    int w = 3 * escala;
    int h = 5 * escala;
    int s = escala;  // Espessura do segmento

    // Segmentos: topo, meio, baixo, esq-cima, esq-baixo, dir-cima, dir-baixo
    bool segmentos[10][7] = {
        {1,0,1,1,1,1,1},  // 0
        {0,0,0,0,0,1,1},  // 1
        {1,1,1,0,1,1,0},  // 2
        {1,1,1,0,0,1,1},  // 3
        {0,1,0,1,0,1,1},  // 4
        {1,1,1,1,0,0,1},  // 5
        {1,1,1,1,1,0,1},  // 6
        {1,0,0,0,0,1,1},  // 7
        {1,1,1,1,1,1,1},  // 8
        {1,1,1,1,0,1,1},  // 9
    };

    if (digito < 0 || digito > 9) return;

    SDL_Rect seg;

    // Topo
    if (segmentos[digito][0]) {
        seg = {x, y, w, s};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Meio
    if (segmentos[digito][1]) {
        seg = {x, y + h/2, w, s};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Baixo
    if (segmentos[digito][2]) {
        seg = {x, y + h - s, w, s};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Esq-cima
    if (segmentos[digito][3]) {
        seg = {x, y, s, h/2 + s};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Esq-baixo
    if (segmentos[digito][4]) {
        seg = {x, y + h/2, s, h/2};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Dir-cima
    if (segmentos[digito][5]) {
        seg = {x + w - s, y, s, h/2 + s};
        SDL_RenderFillRect(renderer, &seg);
    }
    // Dir-baixo
    if (segmentos[digito][6]) {
        seg = {x + w - s, y + h/2, s, h/2};
        SDL_RenderFillRect(renderer, &seg);
    }
}

void desenharNumero(SDL_Renderer* renderer, int numero, int x, int y, int escala) {
    if (numero == 0) {
        desenharDigito(renderer, 0, x, y, escala);
        return;
    }

    // Contar dígitos
    int temp = numero;
    int numDigitos = 0;
    while (temp > 0) {
        numDigitos++;
        temp /= 10;
    }

    // Desenhar da direita para esquerda
    int larguraDigito = 4 * escala;  // 3 de largura + 1 de espaço
    int posX = x + (numDigitos - 1) * larguraDigito;

    while (numero > 0) {
        int digito = numero % 10;
        desenharDigito(renderer, digito, posX, y, escala);
        posX -= larguraDigito;
        numero /= 10;
    }
}

// Desenha letra simples
void desenharLetra(SDL_Renderer* renderer, char c, int x, int y, int escala) {
    int s = escala;
    int w = 4 * escala;
    int h = 5 * escala;
    SDL_Rect r;

    switch(c) {
        case 'A':
            r = {x, y + s, s, h - s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y + s, s, h - s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + s, y, w - 2*s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2, w, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'B':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2 - s/2, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y + s, s, h/2 - s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y + h/2, s, h/2 - s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'C':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'D':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y + s, s, h - 2*s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'E':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'I':
            r = {x + w/2 - s/2, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'L':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'M':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x + s, y + s, s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - 2*s, y + s, s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w/2 - s/2, y + 2*s, s, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'O':
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'P':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y, s, h/2 + s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'R':
            r = {x, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2, w - s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y, s, h/2 + s};
            SDL_RenderFillRect(renderer, &r);
            for (int i = 0; i < h/2; i++) {
                SDL_RenderDrawPoint(renderer, x + w/2 + i, y + h/2 + i);
            }
            break;
        case 'S':
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y, s, h/2 + s};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h/2, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w - s, y + h/2, s, h/2};
            SDL_RenderFillRect(renderer, &r);
            r = {x, y + h - s, w, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'T':
            r = {x, y, w, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + w/2 - s/2, y, s, h};
            SDL_RenderFillRect(renderer, &r);
            break;
        case 'V':
            for (int i = 0; i < h; i++) {
                int offset = (i * w) / (2 * h);
                SDL_RenderDrawPoint(renderer, x + offset, y + i);
                SDL_RenderDrawPoint(renderer, x + w - offset, y + i);
            }
            break;
        case ':':
            r = {x + s, y + h/4, s, s};
            SDL_RenderFillRect(renderer, &r);
            r = {x + s, y + 3*h/4, s, s};
            SDL_RenderFillRect(renderer, &r);
            break;
        case ' ':
            break;
    }
}

void desenharPalavra(SDL_Renderer* renderer, const char* palavra, int x, int y, int escala) {
    int larguraLetra = 5 * escala;
    int posX = x;
    for (int i = 0; palavra[i] != '\0'; i++) {
        desenharLetra(renderer, palavra[i], posX, y, escala);
        posX += larguraLetra;
    }
}

void desenharTelaFimJogo(SDL_Renderer* renderer, EstadoJogo* estado) {
    // Fundo semi-transparente (overlay escuro)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, LARGURA_TELA, ALTURA_TELA};
    SDL_RenderFillRect(renderer, &overlay);

    int centroX = LARGURA_TELA / 2;
    int centroY = ALTURA_TELA / 2;

    if (estado->vitoria) {
        // VITÓRIA - Verde
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        desenharPalavra(renderer, "VITORIA", centroX - 70, centroY - 60, 4);
    } else {
        // DERROTA - Vermelho
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        desenharPalavra(renderer, "DERROTA", centroX - 70, centroY - 60, 4);
    }

    // Estatísticas
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Abatidas
    desenharPalavra(renderer, "ABATIDAS:", centroX - 100, centroY + 20, 2);
    desenharNumero(renderer, estado->navesAbatidas, centroX + 60, centroY + 20, 2);

    // Escaparam
    desenharPalavra(renderer, "ESCAPARAM:", centroX - 100, centroY + 50, 2);
    desenharNumero(renderer, estado->navesEscaparam, centroX + 70, centroY + 50, 2);

    // Total
    desenharPalavra(renderer, "TOTAL:", centroX - 100, centroY + 80, 2);
    desenharNumero(renderer, estado->totalNaves, centroX + 20, centroY + 80, 2);

    // Instrução para sair
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    desenharPalavra(renderer, "ESC", centroX - 30, centroY + 130, 2);
}
