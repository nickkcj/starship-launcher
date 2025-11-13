# Jogo de Defesa Antiaérea

Trabalho de Sistemas Operacionais - UFSC
Implementação de jogo utilizando threads (pthreads) em C++.

## Descrição

Jogo onde o jogador controla uma bateria antiaérea com k lançadores de foguetes para defender a Terra de uma invasão alienígena. As naves descem verticalmente e devem ser abatidas antes de atingir o solo.

**Condições de vitória**: Abater ≥ 50% das naves
**Condições de derrota**: > 50% das naves atingem o solo

## Compilação

```bash
make        # Compila hello world (teste)
make run    # Compila e executa
make clean  # Remove executável
make info   # Mostra divisão de trabalho
```

## Requisitos

- C++ (g++)
- SDL2
- pthreads (POSIX)

### Instalação SDL2 (macOS)
```bash
brew install sdl2
```

## Estrutura do Projeto

```
.
├── src/
│   ├── main.cpp              # [Nick J] Hello World SDL2
│   ├── main_completo.cpp     # [Nick J] Loop principal (versão final)
│   ├── core/                 # Núcleo do jogo
│   │   ├── game.h/cpp        # [Nick J] Estado global, sincronização
│   │   └── renderer.h/cpp    # [Nick J] Sistema de renderização
│   ├── entities/             # Entidades do jogo
│   │   ├── bateria.h/cpp     # [Nick J] Bateria antiaérea
│   │   ├── nave.h/cpp        # [Nick D] Naves e spawn
│   │   └── foguete.h/cpp     # [Nick J] Foguetes e threads
│   └── systems/              # Sistemas e lógica
│       ├── colisao.h/cpp     # [Nick J] Detecção de colisão
│       ├── carregador.h/cpp  # [Nick C] Thread carregador
│       └── dificuldade.h/cpp # [Nick C] Níveis e condições fim
├── Makefile
└── README.md
```

## Controles

- **ESC**: Sair do jogo
- **↑**: Ângulo vertical (90°)
- **←**: Diagonal esquerda (45°)
- **→**: Diagonal direita (45°)
- **ESPAÇO**: Disparar foguete

