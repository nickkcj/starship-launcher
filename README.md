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
│   ├── main.cpp              # [P1] Hello World SDL2
│   ├── main_completo.cpp     # [P1] Loop principal (versão final)
│   ├── core/                 # Núcleo do jogo
│   │   ├── game.h/cpp        # [P1] Estado global, sincronização
│   │   └── renderer.h/cpp    # [P1] Sistema de renderização
│   ├── entities/             # Entidades do jogo
│   │   ├── bateria.h/cpp     # [P1] Bateria antiaérea
│   │   ├── nave.h/cpp        # [P2] Naves e spawn
│   │   └── foguete.h/cpp     # [P1] Foguetes e threads
│   └── systems/              # Sistemas e lógica
│       ├── colisao.h/cpp     # [P1] Detecção de colisão
│       ├── carregador.h/cpp  # [P3] Thread carregador
│       └── dificuldade.h/cpp # [P3] Níveis e condições fim
├── docs/
│   ├── 01-cpp-basico.md      # Tutorial C++ para Python/Java devs
│   └── 02-pthreads.md        # Tutorial pthreads completo
├── DIVISAO_TRABALHO.md       # Divisão entre 3 pessoas
├── GUIA_IMPLEMENTACAO.md     # Passo a passo de como implementar
├── Makefile
└── README.md
```

## Controles

- **ESC**: Sair do jogo
- **↑**: Ângulo vertical (90°)
- **←**: Diagonal esquerda (45°)
- **→**: Diagonal direita (45°)
- **ESPAÇO**: Disparar foguete

## Divisão de Trabalho

- **Pessoa 1 (50%)**: Core do jogo, integração, threads principais
- **Pessoa 2 (25%)**: Naves + relatório
- **Pessoa 3 (25%)**: Carregador, dificuldade + relatório

Ver `DIVISAO_TRABALHO.md` para detalhes.

## Como Implementar

1. Leia os tutoriais em `docs/`
2. Siga o `GUIA_IMPLEMENTACAO.md` passo a passo
3. Implemente etapa por etapa testando continuamente
4. Consulte os comentários TODOs nos arquivos

## Status

- [x] Setup inicial
- [x] Hello World SDL2
- [x] Estrutura modular criada
- [ ] Etapa 1: Desenhar bateria
- [ ] Etapa 2: Controlar ângulo
- [ ] Etapa 3: Sistema de lançadores
- [ ] Etapa 4: Thread carregador
- [ ] Etapa 5: Disparar foguetes
- [ ] Etapa 6: Naves
- [ ] Etapa 7: Colisão
- [ ] Etapa 8: Vitória/Derrota
- [ ] Etapa 9: Níveis de dificuldade

## Prazos

- **23/11/2024**: Entrega do documento de projeto (threads e sincronização)
- **05/12/2024**: Entrega do código final
- **Após 05/12**: Demonstração online com professor
