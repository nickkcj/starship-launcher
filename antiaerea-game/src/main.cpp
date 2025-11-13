// Exemplo 4: Hello World com SDL2
// Abre uma janela gráfica com fundo azul
// Compile: g++ -std=c++11 04-sdl-hello.cpp -o sdl-hello $(sdl2-config --cflags --libs)
// Execute: ./sdl-hello
// Feche a janela clicando no X ou pressionando ESC

#include <SDL.h>
#include <iostream>

const int LARGURA = 800;
const int ALTURA = 600;

int main() {
    std::cout << "=== SDL2 Hello World ===\n";
    std::cout << "Pressione ESC para fechar a janela\n\n";

    // 1. INICIALIZAR SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erro ao inicializar SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    // 2. CRIAR JANELA
    SDL_Window* janela = SDL_CreateWindow(
        "SDL2 - Hello World",           // Título
        SDL_WINDOWPOS_CENTERED,         // Posição X
        SDL_WINDOWPOS_CENTERED,         // Posição Y
        LARGURA,                        // Largura
        ALTURA,                         // Altura
        SDL_WINDOW_SHOWN                // Flags
    );

    if (!janela) {
        std::cout << "Erro ao criar janela: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // 3. CRIAR RENDERIZADOR (quem desenha)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cout << "Erro ao criar renderizador: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 1;
    }

    std::cout << "Janela criada com sucesso!\n";

    // 4. LOOP PRINCIPAL DO JOGO
    bool jogoAtivo = true;
    SDL_Event evento;

    while (jogoAtivo) {
        // A. Processar eventos (input)
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                // Clicou no X
                jogoAtivo = false;
            }
            else if (evento.type == SDL_KEYDOWN) {
                // Pressionou uma tecla
                if (evento.key.keysym.sym == SDLK_ESCAPE) {
                    jogoAtivo = false;
                }
            }
        }

        // B. Renderizar (desenhar)

        // Definir cor de fundo (R, G, B, A)
        SDL_SetRenderDrawColor(renderer, 30, 30, 80, 255);  // Azul escuro
        SDL_RenderClear(renderer);  // Limpar tela com a cor

        // Desenhar um retângulo branco no centro
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Branco
        SDL_Rect retangulo = {LARGURA/2 - 50, ALTURA/2 - 50, 100, 100};
        SDL_RenderFillRect(renderer, &retangulo);

        // Desenhar um retângulo verde (HUD)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Verde
        SDL_Rect hud = {10, 10, 200, 30};
        SDL_RenderFillRect(renderer, &hud);

        // Apresentar na tela
        SDL_RenderPresent(renderer);

        // C. Controlar FPS (~60 FPS)
        SDL_Delay(16);  // ~16ms por frame
    }

    // 5. LIMPAR E ENCERRAR
    std::cout << "Encerrando SDL2...\n";

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    std::cout << "Programa encerrado!\n";
    return 0;
}
