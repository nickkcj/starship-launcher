# Jogo de Defesa Antiaérea

Trabalho de Sistemas Operacionais - UFSC
Implementação de jogo utilizando threads (pthreads) em C++.

## Compilação

```bash
make        # Compila o jogo
make run    # Compila e executa
make clean  # Remove executável
```

## Requisitos

- C++ (g++)
- SDL2
- pthreads

### Instalação SDL2 (macOS)
```bash
brew install sdl2
```

## Estrutura

```
antiaerea-game/
├── src/          # Código fonte
├── docs/         # Documentação e tutoriais
├── Makefile      # Build do projeto
└── README.md
```

## Controles

- ESC: Sair do jogo
- (mais controles serão adicionados)

## Status

- [x] Setup inicial
- [x] Hello World SDL2
- [ ] Estruturas de dados
- [ ] Threads de naves
- [ ] Sistema de disparo
- [ ] Detecção de colisão
- [ ] Níveis de dificuldade
