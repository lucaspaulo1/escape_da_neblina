#include "../include/graph.h"

#include <stdio.h>
#include <stdlib.h>

Grafo* novoGrafo()
{
	Grafo* g = (Grafo*) malloc(sizeof(Grafo));
	g->tamanho = 0;
	g->listaAdj = NULL;

	return g;
}

void deletaGrafo(Grafo* g)
{
	if(g->listaAdj == NULL)
	{
		printf("\nLista de adjacencia vazia!\n");
	}
	else
	{
		Lista* aux = g->listaAdj;

		while(aux != NULL)
		{
			g->listaAdj = g->listaAdj->proximaLista;
			destruirLista(aux);
			aux = g->listaAdj;
		}
	}
	free(g);
}

void insereVertice(Grafo* g)
{
	int numeroVertice = g->tamanho;
	Lista* vertice = criarLista(numeroVertice); //Alocada dinamicamente

	if(g->listaAdj == NULL)
	{
		g->listaAdj = vertice;
	}
	else
	{
		Lista* aux = g->listaAdj;
		while(aux->proximaLista != NULL)
		{
			aux = aux->proximaLista;
		}
		aux->proximaLista = vertice;
	}

	g->tamanho++;	
}

void insereAresta(Grafo* g, int v, double d, int w)
{
	Lista* aux = g->listaAdj;

	if(v < 0 || v > g->tamanho)
	{
		printf("\nVertice invalido!\n");
	}
	else
	{
		while(aux != NULL)
                {
                        if(aux->item == v)
                        {
                                insereFinal(aux, d, w);
                                break;
                        }

                        aux = aux->proximaLista;
                }

	}
}


int quantidadeVertices(Grafo* g)
{
	return g->tamanho;
}

int quantidadeArestas(Grafo* g)
{

	Lista* aux = g->listaAdj;
        int quantidadeVertices = 0;

        if(g->tamanho == 0)
        {
                printf("\nGrafo vazio!\n");

                return -1;
        }
        
        while(aux != NULL)
        {
                quantidadeVertices += aux->vertices;
                aux = aux->proximaLista;
        }
	
	return quantidadeVertices / ARESTAS;
}

int grauMinimo(Grafo* g)
{
	if(g->tamanho == 1)
	{
		return 0;
	}
	else if(g->tamanho < 1)
	{
		printf("Grafo vazio!");
		
		return -1;
	}

	Lista* aux = g->listaAdj;
	int menorGrau = g->tamanho;

	while(aux != NULL)
	{
		if(menorGrau > aux->vertices)
		{
			menorGrau = aux->vertices;
		}

		aux = aux->proximaLista;
	}

	return menorGrau;
}

int grauMaximo(Grafo* g)
{
	if(g->tamanho == 1)
        {
                return 0;
        }
        else if(g->tamanho < 1)
        {
                printf("Grafo vazio!");
                
                return -1;
        }
	
	Lista* aux = g->listaAdj;
        int maiorGrau = aux->vertices;

        while(aux != NULL)
        {
                if(maiorGrau < aux->vertices)
                {
                        maiorGrau = aux->vertices;
                }

                aux = aux->proximaLista;
        }

        return maiorGrau;
}

Lista* vizinhosVertice(Grafo* g, int v)
{
	if (g == NULL) 
	{
        	printf("O ponteiro do grafo é NULL\n");
        	return NULL;
    	}

    	if (g->listaAdj == NULL) 
	{
        	printf("O ponteiro listaAdj do grafo é NULL\n");
        	return NULL;
    	}

    	Lista* aux = g->listaAdj;

    	while (aux != NULL) 
	{
	    	if (aux->item == v) 
		{
            		return aux;
        	}

        	aux = aux->proximaLista;
    	}

    	printf("O indice do vertice nao foi encontrado. Um ponteiro Nulo sera retornado\n");
    	return NULL;
}

void imprimeVizinhos(Grafo* g, int v)
{
	Lista* aux = g->listaAdj;
	
	while(aux != NULL)
	{
		if(aux->item == v)
		{
			imprimirLista(aux);
		}
		
		aux = aux->proximaLista;
	}	
}

void imprimeGrafo(Grafo* g)
{
	int n = quantidadeVertices(g);
	
	for(int i = 0; i < n; i++)
	{
		printf("%d :", i);
		imprimeVizinhos(g, i);
	}

	printf("\n");
}





