// Nick J - Loop principal do jogo (evoluindo aos poucos)
// Versão atual: Etapa 5 - Disparar foguetes

#include <SDL.h>
#include <iostream>
#include "entities/bateria.h"
#include "entities/foguete.h"
#include "core/game.h"
#include "core/renderer.h"

const int LARGURA = 800;
const int ALTURA = 600;

int main() {
    std::cout << "=== Jogo de Defesa Antiaérea ===\n";
    std::cout << "Controles:\n";
    std::cout << "  ↑ (UP)    - Vertical\n";
    std::cout << "  ← (LEFT)  - Diagonal Esquerda\n";
    std::cout << "  → (RIGHT) - Diagonal Direita\n";
    std::cout << "  Q         - Horizontal Esquerda\n";
    std::cout << "  E         - Horizontal Direita\n";
    std::cout << "  ESPAÇO    - DISPARAR!\n";
    std::cout << "  ESC       - Sair\n\n";

    // 1. INICIALIZAR SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erro ao inicializar SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    // 2. CRIAR JANELA
    SDL_Window* janela = SDL_CreateWindow(
        "Defesa Antiaérea",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGURA,
        ALTURA,
        SDL_WINDOW_SHOWN
    );

    if (!janela) {
        std::cout << "Erro ao criar janela: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // 3. CRIAR RENDERIZADOR
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

    // 4. INICIALIZAR ESTADO DO JOGO
    EstadoJogo estado;
    inicializarJogo(&estado, 0);  // 0 = dificuldade média por enquanto

    // 5. CRIAR BATERIA
    Bateria* bateria = criarBateria(LARGURA/2, ALTURA - 80);
    estado.bateria = bateria;  // Associar bateria ao estado

    // 6. LOOP PRINCIPAL
    bool jogoAtivo = true;
    SDL_Event evento;

    while (jogoAtivo) {
        // A. Processar eventos (input)
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                jogoAtivo = false;
            }
            else if (evento.type == SDL_KEYDOWN) {
                switch(evento.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        jogoAtivo = false;
                        break;

                    // Controle de ângulo
                    case SDLK_UP:
                        mudarAngulo(bateria, VERTICAL);
                        std::cout << "Ângulo: VERTICAL\n";
                        break;
                    case SDLK_LEFT:
                        mudarAngulo(bateria, DIAGONAL_ESQ);
                        std::cout << "Ângulo: DIAGONAL ESQUERDA\n";
                        break;
                    case SDLK_RIGHT:
                        mudarAngulo(bateria, DIAGONAL_DIR);
                        std::cout << "Ângulo: DIAGONAL DIREITA\n";
                        break;
                    case SDLK_q:
                        mudarAngulo(bateria, HORIZONTAL_ESQ);
                        std::cout << "Ângulo: HORIZONTAL ESQUERDA\n";
                        break;
                    case SDLK_e:
                        mudarAngulo(bateria, HORIZONTAL_DIR);
                        std::cout << "Ângulo: HORIZONTAL DIREITA\n";
                        break;

                    // Disparar foguete
                    case SDLK_SPACE: {
                        pthread_mutex_lock(&estado.mutexLancadores);

                        // Procurar lançador carregado
                        int lancadorUsado = -1;
                        for(int i = 0; i < estado.numLancadores; i++) {
                            if(estado.lancadores[i] == 1) {
                                lancadorUsado = i;
                                break;
                            }
                        }

                        if(lancadorUsado == -1) {
                            std::cout << "VAZIO! Sem foguetes disponíveis\n";
                        } else {
                            // Criar foguete na posição da bateria
                            Foguete* fog = criarFoguete(bateria->x, bateria->y, bateria->angulo);

                            // Adicionar na lista (mutex!)
                            pthread_mutex_lock(&estado.mutexGeral);
                            estado.foguetes.push_back(fog);
                            pthread_mutex_unlock(&estado.mutexGeral);

                            // Criar estrutura de dados para thread
                            struct DadosFoguete {
                                Foguete* foguete;
                                EstadoJogo* estado;
                            };
                            DadosFoguete* dados = new DadosFoguete;
                            dados->foguete = fog;
                            dados->estado = &estado;

                            // Criar thread do foguete
                            pthread_create(&fog->thread, nullptr, threadFoguete, dados);
                            pthread_detach(fog->thread);  // Detach para não precisar fazer join

                            // Descarregar lançador
                            estado.lancadores[lancadorUsado] = 0;

                            // Sinalizar carregador (quando Nick C implementar)
                            pthread_cond_signal(&estado.condCarregador);

                            std::cout << "DISPAROU do lançador " << lancadorUsado << "!\n";
                        }

                        pthread_mutex_unlock(&estado.mutexLancadores);
                        break;
                    }
                }
            }
        }

        // B. Renderizar (desenhar)

        // Fundo azul escuro (céu noturno)
        SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
        SDL_RenderClear(renderer);

        // Linha do chão (cinza)
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderDrawLine(renderer, 0, ALTURA - 50, LARGURA, ALTURA - 50);

        // Desenhar bateria
        desenharBateria(renderer, bateria);

        // Desenhar foguetes
        pthread_mutex_lock(&estado.mutexGeral);
        for(auto fog : estado.foguetes) {
            desenharFoguete(renderer, fog);
        }
        pthread_mutex_unlock(&estado.mutexGeral);

        // Desenhar HUD (lançadores)
        desenharHUD(renderer, &estado);

        // Apresentar na tela
        SDL_RenderPresent(renderer);

        // C. Controlar FPS (~60 FPS)
        SDL_Delay(16);
    }

    // 7. LIMPAR E ENCERRAR
    std::cout << "Encerrando...\n";

    finalizarJogo(&estado);
    destruirBateria(bateria);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    std::cout << "Jogo encerrado!\n";
    return 0;
}
