#ifndef GRAPH_HPP
#define GRAPH_HPP
#define ARESTAS 2

#include "./no.h"
#include "./lista_encadeada.h"

/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Nenhuma outra alteração neste arquivo é permitida
 */


/*  Você deve implementar struct s_grafo como um TAD que irá armazenar
 * os dados de um grafo. Lembrando que a estratégia utilizada deve ser uma
 * lista de adjacencia e deve ser implementada como uma lista encadeada.
 */
typedef struct s_grafo 
{
	int tamanho;
	Lista* listaAdj;	
} Grafo;

Grafo* novoGrafo();
void deletaGrafo(Grafo* g);
void insereVertice(Grafo* g);
void insereAresta(Grafo* g, int v, double d, int w);
int quantidadeVertices(Grafo* g);
int quantidadeArestas(Grafo* g);
int grauMinimo(Grafo* g);
int grauMaximo(Grafo* g);
Lista* vizinhosVertice(Grafo* g, int v);
void imprimeVizinhos(Grafo* g, int v);
void imprimeGrafo(Grafo* g);

#endif
