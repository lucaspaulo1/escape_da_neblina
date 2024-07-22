#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../include/no.h"

/*
 * TAD que representa uma 4-upla que sera utilizada como elemento em uma Fila de Prioridade (Heap)
 */
typedef struct 
{
	double d; // Representa a distancia 
	int v; // Representa o indice do vertice
	int portais; // Representa a quantidade de portais usados
	double h; // Representa a heuristica do distancia de um  ponto no plano cartesiano ate seu destino
} Tupla;

/*
 * TAD que representa um Heap (fila de prioridade) binario implementado como um vetor de Tuplas
 */
typedef struct
{
	int tamanho; // Quantidade de elementos que o Heap suporta
	int ocupados; // Quantidade de espaços ocupados no Heap
	Tupla* vetor; // Vetor de Tuplas
} Heap;

/*
 * Cria um Heap de tamanho 'n'
 */
Heap* criarHeap(int n);

/*
 * Modifica os valores de uma tupla
 */
void setTupla(Tupla* tupla, double dist, int vert, int port, double hstc);

/*
 * Compara duas tuplas diferentes para averiguar qual delas tem maior prioridade
 */
int compararTuplas(Tupla a, Tupla b);

/*
 * Pega o 'pai' de um registro (Tupla)
 */
int getAncestral(int i);

/*
 * Pega o 'filho' esquerdo de um registro
 */
int getSucessorEsq(int i);

/*
 * Pega o 'filho' direito de um registro
 */
int getSucessorDir(int i);


/*
 * Destroi e desaloca memoria de um Heap
 */
void destruirHeap(Heap* heap);

/*
 * Insere um registro respeitando a estrutura do Heap
 */
void inserirNoHeap(Heap* heap, double d, int v, int portais, double h);

/*
 * Remove e retorna a raiz de um Heap respeitando a estrutura e concertando-a caso necessario (Heapfy)
 */
Tupla removeNoHeap(Heap* heap);

/*
 * Printa todos registros do Heap
 */
void imprimirHeap(Heap* heap);

/*
 * Verifica se o Heap esta vazio
 */
int empty(Heap* heap);

#endif
