// PESSOA 3 - Thread carregador de foguetes

#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <pthread.h>

// Forward declaration
struct EstadoJogo;

// Thread que carrega lançadores automaticamente
void* threadCarregador(void* arg);

#endif
