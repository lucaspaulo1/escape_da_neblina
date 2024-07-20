#include "../include/ponto.h"
#include "../include/no.h"
#include "../include/lista_encadeada.h"
#include "../include/graph.h"
#include "../include/fila_prioridade.h"
#include "../include/dijkstra.h"


#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define ENDL "\n"


static int minimo(int a, int b) {
    if(a > b) return b;

    return a;
}


int main()
{
	int n, m ,k; // Numero de clareiras, trilhas e portais, respectivamente
	double x, y; // Coordenadas de uma clareira no plano
    	int u, v; // Trilha entre duas clareiras
    	double s; // Energia de Link
    	int q; // Quantidade de portais que podem ser utilizados
    	double d; // Distancia euclideana de um ponto para outro
	Ponto* pontos; // Coordenadas dos vertices
	Ponto saida;; // Representa a saida da floresta
	int j; // Indice
	double* distancias; // Vetor de distancias euclidianas de cada clareira para a saida

	Grafo* grafo = novoGrafo();
	
    	scanf("%d %d %d", &n, &m, &k);

	pontos = (Ponto*) malloc(sizeof(Ponto) * (n + 1));	
	distancias = (double*) malloc(sizeof(double) * (n + 1));

	// Verificacao da alocacao de memoria
	if(pontos == NULL)
	{
		printf("A alocacao do vetor de pontos falhou!");
		exit(1);
	}

	if(distancias == NULL)
	{
		printf("A alocacao do vetor de distancias falhou!");
		exit(1);
	}

	// Coordenadas das clareiras (vertices)
    	for(j = 0; j < n; j++)
    	{
        	scanf("%lf %lf", &x, &y);
		insereVertice(grafo); // Criar um vertice 'i'
		setPonto(&pontos[j], x, y); // Coloca as coordenadas do vertice no vetor
    	}

	saida = pontos[j];
    
	// Trilhas entre clareiras (arestas)
    	for(int i = 0; i < m; i++)
    	{
        	scanf("%d %d", &u, &v);
		d = distanciaXY(pontos[u], pontos[v]);
		insereAresta(grafo, u, d, v); // Cria a aresta peso (distancia)
    	}
    
	// Clareiras com portais (arestas)
    	for(int i = 0; i < k; i++)
    	{
        	scanf("%d %d", &u, &v);
		insereAresta(grafo, u, 0, v); // Cria a aresta com peso 0 (zero)
    	}

    	scanf("%lf %d", &s, &q);

	// Distancias ate a saida
	for(int i = 0; i < n; i++)
	{
		distancias[i] = distanciaXY(pontos[i], saida);
	}
			
	imprimeGrafo(grafo);
	
	free(pontos);

    	return 0;
}
