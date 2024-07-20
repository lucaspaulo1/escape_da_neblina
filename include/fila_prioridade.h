#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../include/no.h"

typedef struct 
{
	double d; // Representa a distancia 
	int v; // Representa o indice do vertice
	int portais; // Representa a quantidade de portais usados
	double h; // Representa a heuristica do distancia de um  ponto no plano cartesiano ate seu destino
} Tupla;

typedef struct
{
	int tamanho;
	int ocupados;
	Tupla* vetor;
} Heap;


Heap* criarHeap(int n);
void setTupla(Tupla* tupla, double dist, int vert, int port, double hstc);
int compararTuplas(Tupla a, Tupla b);
int getAncestral(int i);
int getSucessorEsq(int i);
int getSucessorDir(int i);
void destruirHeap(Heap* heap);
void inserirNoHeap(Heap* heap, double d, int v, int portais, double h);
Tupla removeNoHeap(Heap* heap);
void imprimirHeap(Heap* heap);
int empty(Heap* heap);

#endif
