#ifndef A_ESTRELA_H
#define A_ESTRELA_H

#include "./include/no.h"
#include "./include/ponto.h"
#include "./include/grafo.h"
#include "./include/fila_prioridade.h"

/**
 * Calcula o caminho mais curto usando o algoritmo A*.
 *
 * @param g O grafo representando as clareiras e trilhas.
 * @param dist Um vetor de distâncias (em linha reta) de cada clareira para a saida.
 * @param energia A quantidade de energia que Linque possui.
 * @param num_portais O número máximo de portais que Linque pode usar.
 * @param fonte A clareira inicial (sempre 0).
 * @param objetivo A clareira de saída (sempre n - 1).
 */
void aEstrela(Grafo* g, double* dist, double energia, int num_portais, int fonte, int objetivo);

#endif
