#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../include/no.h"
#include "../include/graph.h"
#include "../include/fila_prioridade.h"

double* dijkstraPadrao(Grafo *g, int fonte);
double* dijkstra(Grafo* g, double energia, int num_portais, int fonte);

#endif
