// Nick D - Implementação das naves

#include "nave.h"
#include "../core/game.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>

SDL_Texture* carregarTexturaNave(SDL_Renderer* renderer, const char* caminhoImagem) {
    // Carregar imagem PNG usando SDL_image
    SDL_Surface* surface = IMG_Load(caminhoImagem);
    if (!surface) {
        std::cout << "Erro ao carregar PNG: " << IMG_GetError() << "\n";
        return nullptr;
    }

    // Converter para textura
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!textura) {
        std::cout << "Erro ao criar textura: " << SDL_GetError() << "\n";
    }

    return textura;
}

Nave* criarNave(int x, int velocidade) {
    // Alocar memória para a nave
    Nave* nave = new Nave;
    
    // Inicializar posição e propriedades
    nave->x = x;
    nave->y = 0;  // Começa no topo da tela
    nave->velocidade = velocidade;
    nave->ativa = true;
    nave->textura = nullptr;  // Será carregada no main.cpp se necessário
    
    return nave;
}

void desenharNave(SDL_Renderer* renderer, Nave* nave) {
    if (!nave || !nave->ativa) return;

    // Se tem textura PNG, desenhar ela rotacionada 180° (caindo de cabeça para baixo)
    if (nave->textura) {
        SDL_Rect destino = {nave->x - 20, nave->y - 20, 40, 40};
        SDL_RenderCopyEx(renderer, nave->textura, nullptr, &destino, 
                         180.0,  // Rotação de 180 graus
                         nullptr, SDL_FLIP_NONE);
    } else {
        // Fallback: retângulo vermelho se não tiver PNG
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = {nave->x - 15, nave->y - 10, 30, 20};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void* threadNave(void* arg) {
    // Estrutura auxiliar para passar dados para a thread
    struct DadosNave {
        EstadoJogo* estado;
        Nave* nave;
    };
    
    DadosNave* dados = (DadosNave*)arg;
    EstadoJogo* estado = dados->estado;
    Nave* nave = dados->nave;
    
    // Loop principal: mover a nave para baixo
    while (nave->ativa && estado->jogoAtivo) {
        // Mover nave para baixo
        nave->y += nave->velocidade;
        
        // Verificar se chegou no chão (50 pixels é a margem inferior)
        if (nave->y > ALTURA_TELA - 50) {
            // Nave escapou! Marcar como inativa e incrementar contador
            pthread_mutex_lock(&estado->mutexGeral);
            nave->ativa = false;
            estado->navesEscaparam++;
            pthread_mutex_unlock(&estado->mutexGeral);
            
            std::cout << "Nave escapou! Total escapadas: " << estado->navesEscaparam << "\n";
        }
        
        // Dormir um pouco para controlar velocidade (aproximadamente 60 FPS)
        usleep(16000);  // 16ms = ~60 FPS
    }
    
    delete dados;  // Liberar estrutura auxiliar
    return nullptr;
}

void* threadSpawnNaves(void* arg) {
    EstadoJogo* estado = (EstadoJogo*)arg;

    // Usar parâmetros de dificuldade do estado do jogo
    int velocidade = estado->velocidadeNave;
    int intervaloSpawn = estado->intervaloSpawn;

    std::cout << "Spawn configurado: velocidade=" << velocidade
              << ", intervalo=" << intervaloSpawn << "s\n";

    // Inicializar gerador de números aleatórios
    srand(time(nullptr));

    // Loop: criar naves até atingir o total ou jogo acabar
    while (estado->jogoAtivo) {
        pthread_mutex_lock(&estado->mutexGeral);
        int navesAtuais = estado->naves.size();
        int total = estado->totalNaves;
        pthread_mutex_unlock(&estado->mutexGeral);

        // Verificar se já criou todas as naves necessárias
        if (navesAtuais >= total) {
            break;
        }

        // Criar nave em posição X aleatória
        int x = 50 + (rand() % (LARGURA_TELA - 100));  // Entre 50 e LARGURA-50
        Nave* nova = criarNave(x, velocidade);

        // Atribuir textura compartilhada
        nova->textura = estado->texturaNave;

        // Adicionar na lista (proteger com mutex)
        pthread_mutex_lock(&estado->mutexGeral);
        estado->naves.push_back(nova);
        pthread_mutex_unlock(&estado->mutexGeral);

        // Criar estrutura de dados para passar à thread
        struct DadosNave {
            EstadoJogo* estado;
            Nave* nave;
        };
        DadosNave* dados = new DadosNave;
        dados->estado = estado;
        dados->nave = nova;

        // Criar thread para mover esta nave
        pthread_create(&nova->thread, nullptr, threadNave, dados);
        pthread_detach(nova->thread);  // Detach para não precisar fazer join

        std::cout << "Nova nave criada na posição X=" << x << " (vel=" << velocidade << ")\n";

        // Aguardar intervalo antes de criar próxima nave
        sleep(intervaloSpawn);
    }

    std::cout << "Thread de spawn encerrada\n";
    return nullptr;
}

void destruirNave(Nave* nave) {
    if (nave) {
        // NÃO destruir textura aqui - ela é compartilhada!
        // A textura será destruída no finalizarJogo
        delete nave;
    }
}
