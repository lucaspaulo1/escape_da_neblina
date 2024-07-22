#include "../include/no.h"
#include "../include/grafo_matriz_adjacencia.h"

#include "stdio.h"
#include "stdlib.h"

GrafoMatriz* criaMatriz(int n)
{
	GrafoMatriz* grafo = (GrafoMatriz*) malloc(sizeof(grafo)); // Aloca dimaicamente o Grafo a ser retornado
	
	if(grafo == NULL)
	{
		printf("A alocacao de memoria para o 'GrafoMatriz' falhou\n");

		exit(1);
	}

	grafo->n = n;	
	grafo->matriz = (No**) malloc(sizeof(No*) * n); // Aloca dinamicamente uma matriz quadrada de tamanho 'n'

	// Verifica se a matriz foi criada corretamente
	if(grafo->matriz == NULL)
	{
		printf("A alocacao de memoria da Matriz de adjacencia falhou!\n");

		free(grafo); // Libera a memoria alocada para o grafo
		exit(1);
	}

	// Aloca dinamicamente as linhas da matriz 
	for (int i = 0; i < n; i++) 
	{
    		grafo->matriz[i] = (No*) malloc(sizeof(No) * n);
		if(grafo->matriz[i] == NULL)
		{
			printf("a alocacao de memoria para a linha '%d' da matriz falhou!\n", i);

			// Desaloca a memoria alocada anteriormente 
			for(int j = 0; j < n; j++) free(grafo->matriz[j]);
			free(grafo->matriz);
			free(grafo);

			exit(1);
		}
	}

	return grafo;
}

void destroiMatriz(GrafoMatriz* g)
{
	int m = g->n;
	for(int i = 0; i < m; i++)
	{
		free(g->matriz[i]);
	}

	free(g->matriz);
	free(g);
}

void insereArestaNaMatriz(GrafoMatriz* g, int i, int j, double d)
{
	No* aux = &g->matriz[i][j];
	int m = g->n; // Quantidade de vertices

	if(i > m || j > m)
	{
		printf("Vertice Invalido!\n");
	}

	//setarNo(&aux, d, 1); // O '1' define que existe uma aresta com peso 'd' entre o vertice [i][j]
	aux->vertice = 1;
	aux->distancia = d;
}

void imprimeMatriz(GrafoMatriz* g)
{
	int m = g->n; // Tamanho da matriz
	int v = 0; // Representa o vertice 
	double d = 0; // Tamanho da aresta ponderada
		      
	puts("Matriz de adjacencia: ");
	for(int i = 0; i < m; i++)
	{
		printf("%d: ", i); // Printa o vertice 'i'
		for(int j = 0; j < m; j++)
		{	
			v = g->matriz[i][j].vertice;
			d = g->matriz[i][j].distancia;

			// Verifica se existe '1', ou seja, se existe aresta entre 'i' e 'j'
			if(v == 1)
			{
				printf("(%lf, %d)", d, j); // Printa os vizinhos do vertice 'i'
			}
		}
		puts("");
	}
	puts("");
}




