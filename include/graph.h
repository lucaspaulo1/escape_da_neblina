#ifndef GRAPH_HPP
#define GRAPH_HPP
#define ARESTAS 2

#include "./no.h"
#include "./lista_encadeada.h"

/*
 * TAD grafo implementado como uma lista de lista de adjacencias
 */
typedef struct s_grafo 
{
	int tamanho;
	Lista* listaAdj;	
} Grafo;

/*
 * Cria um novo grafo
 */
Grafo* novoGrafo();

/*
 * Deleta um grafo desalocando toda memoria usada
 */
void deletaGrafo(Grafo* g);

/*
 * Insere vertice no grafo
 */
void insereVertice(Grafo* g);

/*
 *  Insere uma aresta com os valores especificados
 */
void insereAresta(Grafo* g, int v, double d, int w);


/*
 * Retorna a quantidade de vertices do grafo
 */
int quantidadeVertices(Grafo* g);

/*
 * Retorna a quantidade de arestas do grafo
 */
int quantidadeArestas(Grafo* g);

/*
 * Retorna o grauMinimo (vertice com a menor quantidade de arestas) do grafo
 */
int grauMinimo(Grafo* g);

/*
 * Retorna o grauMaximo (vertice com a maior quantidade de arestas) do grafo
 */
int grauMaximo(Grafo* g);

/*
 * Retorna a lista que representa os vizinhos (vertices unidos por aresta) de um determinado vertice do grafo
 */
Lista* vizinhosVertice(Grafo* g, int v);

/*
 * Imprime os vizinhos de um vertice
 */
void imprimeVizinhos(Grafo* g, int v);

void imprimeGrafo(Grafo* g);

#endif
