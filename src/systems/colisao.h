// PESSOA 1 - Detecção de colisão

#ifndef COLISAO_H
#define COLISAO_H

#include "../entities/nave.h"
#include "../entities/foguete.h"

// Verifica se foguete colidiu com nave
bool verificarColisao(Foguete* fog, Nave* nave);

// Verifica todas as colisões possíveis (chamado pelo loop principal)
void verificarTodasColisoes(struct EstadoJogo* estado);

#endif
