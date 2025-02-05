#ifndef NO_H
#define NO_H

/*
 * Definicao do TAD 'No' que servira para representar um vertice e uma distancia associada ao vertice (aresta ponderada) em um grafo
 */
typedef struct no
{
	double distancia; // Representa o valor da aresta ponderada que liga o vertice
	int vertice; // Representa o indice do vertice
	struct no* proximo; // Representa o proximo vertice (vizinho) 
} No;

/*
 * Cria e retorna um No com indice especidicado
 */
No* criarNo(double d, int v);

/*
 * Retorna o atributo 'distancia' do No especificado
 */
double getDistancia(No* no);

/*
 * Retorna o atributo 'distancia' do No especificado
 */
int getVertice(No* no);

/*
 * Altera os atributos do No especificado
 */
void setarNo(No* no, double d, int v);

/*
 * Printa os atributos do No
 */
void imprimirNo(No* no);

#endif
