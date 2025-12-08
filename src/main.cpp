// Nick J - Loop principal do jogo

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "entities/bateria.h"
#include "entities/foguete.h"
#include "entities/nave.h"
#include "core/game.h"
#include "core/renderer.h"
#include "systems/colisao.h"
#include "systems/carregador.h"
#include "systems/dificuldade.h"

const int LARGURA = 800;
const int ALTURA = 600;

// Variável global da fonte (para usar em todo o jogo)
TTF_Font* fonteGrande = nullptr;
TTF_Font* fonteMedia = nullptr;
TTF_Font* fontePequena = nullptr;

// Função auxiliar para renderizar texto centralizado
void renderizarTextoCentralizado(SDL_Renderer* renderer, TTF_Font* fonte,
                                  const char* texto, int centerX, int centerY,
                                  SDL_Color cor) {
    SDL_Surface* surface = TTF_RenderText_Blended(fonte, texto, cor);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destino = {centerX - surface->w/2, centerY - surface->h/2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destino);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// Função para desenhar o menu de seleção de dificuldade
void desenharMenu(SDL_Renderer* renderer, int opcaoSelecionada) {
    // Fundo
    SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
    SDL_RenderClear(renderer);

    // Cores
    SDL_Color amarelo = {255, 200, 0, 255};
    SDL_Color branco = {255, 255, 255, 255};
    SDL_Color preto = {0, 0, 0, 255};
    SDL_Color cinza = {150, 150, 150, 255};

    // Título
    renderizarTextoCentralizado(renderer, fonteGrande, "DEFESA ANTIAEREA", LARGURA/2, 100, amarelo);

    // Opções de dificuldade
    const char* nomes[] = {"FACIL", "MEDIO", "DIFICIL"};
    const char* descricoes[] = {
        "2 lancadores | Recarga 3s | 10 naves",
        "3 lancadores | Recarga 2s | 15 naves",
        "5 lancadores | Recarga 1s | 20 naves"
    };

    for (int i = 0; i < 3; i++) {
        int y = 220 + i * 90;
        SDL_Rect box = {LARGURA/2 - 160, y - 10, 320, 70};

        if (i == opcaoSelecionada) {
            // Selecionada: fundo verde
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
            SDL_RenderFillRect(renderer, &box);
            renderizarTextoCentralizado(renderer, fonteMedia, nomes[i], LARGURA/2, y + 10, preto);
            renderizarTextoCentralizado(renderer, fontePequena, descricoes[i], LARGURA/2, y + 38, preto);
        } else {
            // Não selecionada: borda cinza
            SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
            SDL_RenderDrawRect(renderer, &box);
            renderizarTextoCentralizado(renderer, fonteMedia, nomes[i], LARGURA/2, y + 10, branco);
            renderizarTextoCentralizado(renderer, fontePequena, descricoes[i], LARGURA/2, y + 38, cinza);
        }
    }

    // Instruções
    renderizarTextoCentralizado(renderer, fontePequena, "Setas: Navegar | Enter: Selecionar | 1-3: Atalho",
                                 LARGURA/2, ALTURA - 50, cinza);

    SDL_RenderPresent(renderer);
}

// Função do menu de seleção de dificuldade
int menuDificuldade(SDL_Renderer* renderer) {
    int opcaoSelecionada = 1;  // Começa no MEDIO
    bool menuAtivo = true;
    SDL_Event evento;

    std::cout << "\n=== MENU DE DIFICULDADE ===\n";
    std::cout << "Use SETAS para navegar, ENTER para selecionar\n";

    while (menuAtivo) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                return -1;
            }
            else if (evento.type == SDL_KEYDOWN) {
                switch (evento.key.keysym.sym) {
                    case SDLK_UP:
                        opcaoSelecionada = (opcaoSelecionada - 1 + 3) % 3;
                        break;
                    case SDLK_DOWN:
                        opcaoSelecionada = (opcaoSelecionada + 1) % 3;
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        menuAtivo = false;
                        break;
                    case SDLK_ESCAPE:
                        return -1;
                    case SDLK_1:
                        return 0;  // FACIL
                    case SDLK_2:
                        return 1;  // MEDIO
                    case SDLK_3:
                        return 2;  // DIFICIL
                }
            }
        }
        desenharMenu(renderer, opcaoSelecionada);
        SDL_Delay(16);
    }

    const char* nomes[] = {"FACIL", "MEDIO", "DIFICIL"};
    std::cout << "Dificuldade: " << nomes[opcaoSelecionada] << "\n\n";
    return opcaoSelecionada;
}

int main() {
    std::cout << "=== Jogo de Defesa Antiaerea ===\n";

    // 1. INICIALIZAR SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erro ao inicializar SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    // 1.1 INICIALIZAR SDL_TTF
    if (TTF_Init() < 0) {
        std::cout << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // 2. CRIAR JANELA
    SDL_Window* janela = SDL_CreateWindow(
        "Defesa Antiaerea",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGURA,
        ALTURA,
        SDL_WINDOW_SHOWN
    );

    if (!janela) {
        std::cout << "Erro ao criar janela: " << SDL_GetError() << "\n";
        TTF_Quit();
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
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // 3.1 CARREGAR FONTES (usa fonte do sistema)
    const char* caminhosFonte[] = {
        "/System/Library/Fonts/Helvetica.ttc",           // macOS
        "/System/Library/Fonts/SFNSMono.ttf",            // macOS SF Mono
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Linux
        "/usr/share/fonts/TTF/DejaVuSans.ttf",           // Linux alternativo
        "C:\\Windows\\Fonts\\arial.ttf"                  // Windows
    };

    const char* fonteUsada = nullptr;
    for (const char* caminho : caminhosFonte) {
        fonteGrande = TTF_OpenFont(caminho, 36);
        if (fonteGrande) {
            fonteUsada = caminho;
            fonteMedia = TTF_OpenFont(caminho, 24);
            fontePequena = TTF_OpenFont(caminho, 16);
            break;
        }
    }

    if (!fonteGrande) {
        std::cout << "Erro: Nenhuma fonte encontrada!\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    std::cout << "Fonte carregada: " << fonteUsada << "\n";

    // 3.5 MOSTRAR MENU DE DIFICULDADE
    int dificuldade = menuDificuldade(renderer);
    if (dificuldade == -1) {
        TTF_CloseFont(fonteGrande);
        TTF_CloseFont(fonteMedia);
        TTF_CloseFont(fontePequena);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(janela);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    // Mostrar controles após selecionar dificuldade
    std::cout << "Controles:\n";
    std::cout << "  UP        - Vertical (90 graus)\n";
    std::cout << "  LEFT      - Diagonal Esquerda (45 graus)\n";
    std::cout << "  RIGHT     - Diagonal Direita (45 graus)\n";
    std::cout << "  Q         - Horizontal Esquerda (180 graus)\n";
    std::cout << "  E         - Horizontal Direita (180 graus)\n";
    std::cout << "  ESPACO    - DISPARAR!\n";
    std::cout << "  ESC       - Sair\n\n";

    // 4. INICIALIZAR ESTADO DO JOGO
    EstadoJogo estado;
    inicializarJogo(&estado, dificuldade);
    estado.renderer = renderer;  // Passar renderer para o estado

    // 4.1 CARREGAR TEXTURA DA NAVE
    estado.texturaNave = carregarTexturaNave(renderer, "assets/ship.png");
    if (!estado.texturaNave) {
        std::cout << "Aviso: Textura da nave não carregada, usando retângulo vermelho\n";
    }

    // 5. CRIAR BATERIA
    Bateria* bateria = criarBateria(LARGURA/2, ALTURA - 80);
    estado.bateria = bateria;  // Associar bateria ao estado

    // 5.1 CRIAR THREAD DO CARREGADOR
    pthread_t threadCarreg;
    pthread_create(&threadCarreg, nullptr, threadCarregador, &estado);

    // 5.2 CRIAR THREAD DE SPAWN DE NAVES
    pthread_t threadSpawn;
    pthread_create(&threadSpawn, nullptr, threadSpawnNaves, &estado);

    // 6. LOOP PRINCIPAL
    bool jogoAtivo = true;
    bool fimDeJogo = false;
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

        // Desenhar naves
        pthread_mutex_lock(&estado.mutexGeral);
        for(auto nave : estado.naves) {
            desenharNave(renderer, nave);
        }
        pthread_mutex_unlock(&estado.mutexGeral);

        // Desenhar foguetes
        pthread_mutex_lock(&estado.mutexGeral);
        for(auto fog : estado.foguetes) {
            desenharFoguete(renderer, fog);
        }
        pthread_mutex_unlock(&estado.mutexGeral);

        // Desenhar HUD (lançadores)
        desenharHUD(renderer, &estado);

        // Verificar condição de fim de jogo
        if (!fimDeJogo) {
            // Só verifica se todas as naves já apareceram
            int navesProcessadas = estado.navesAbatidas + estado.navesEscaparam;
            if (navesProcessadas >= estado.totalNaves) {
                fimDeJogo = true;
                estado.jogoAtivo = false;  // Parar threads
                estado.vitoria = verificarVitoria(&estado);

                if (estado.vitoria) {
                    std::cout << "\n*** VITÓRIA! ***\n";
                } else {
                    std::cout << "\n*** DERROTA! ***\n";
                }
            }
        }

        // Desenhar tela de fim de jogo (se acabou)
        if (fimDeJogo) {
            desenharTelaFimJogo(renderer, &estado);
        }

        // Apresentar na tela
        SDL_RenderPresent(renderer);

        // C. Verificar colisões
        if (!fimDeJogo) {
            verificarTodasColisoes(&estado);
        }

        // D. Controlar FPS (~60 FPS)
        SDL_Delay(16);
    }

    // 7. LIMPAR E ENCERRAR
    std::cout << "Encerrando...\n";

    // Encerrar threads
    estado.jogoAtivo = false;
    pthread_cond_signal(&estado.condCarregador);  // Acordar carregador para sair do loop
    pthread_join(threadCarreg, nullptr);
    pthread_join(threadSpawn, nullptr);

    // Mostrar estatísticas finais
    std::cout << "\n=== ESTATÍSTICAS ===\n";
    std::cout << "Naves abatidas: " << estado.navesAbatidas << "\n";
    std::cout << "Naves escaparam: " << estado.navesEscaparam << "\n";
    std::cout << "Total de naves: " << estado.totalNaves << "\n";

    finalizarJogo(&estado);
    destruirBateria(bateria);

    // Limpar fontes
    TTF_CloseFont(fonteGrande);
    TTF_CloseFont(fonteMedia);
    TTF_CloseFont(fontePequena);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(janela);
    TTF_Quit();
    SDL_Quit();

    std::cout << "Jogo encerrado!\n";
    return 0;
}
