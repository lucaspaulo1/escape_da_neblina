#ifndef GRAFO_MATRIZ_ADJACENCIA
#define GRAFO_MATRIZ_ADJACENCIA

#include "./no.h"

/*
 * TAD que representa um grafo implementado como uma matriz de adjacencia, onde cada elemento da matriz eh um struct 'No'
 */
typedef struct
{
	int n; // Representa a quantidade de vertices do grafo
	No** matriz; // Matriz de nos
} GrafoMatriz; 

/*
 * Cria um GrafoMatriz e retorna o endereco da estrututra
 */
GrafoMatriz* criaMatriz(int n);


/*
 * Destroi um GrafoMatriz desalocando toda memoria alocada para ele anteriormente
 */
void destroiMatriz(GrafoMatriz* g);

/*
 * Insere uma aresta ponderada na Matriz, ou seja, no atributo 'vertice' do No especificado sera marcado como '1' para representar que existe uma aresta de peso 'd' entre entre o vertice 'i' e 'j' do grafo
 */
void insereArestaNaMatriz(GrafoMatriz* g, int i, int j, double d);

/*
 * Printa o grafo
 */
void imprimeMatriz(GrafoMatriz* g);

#endif
