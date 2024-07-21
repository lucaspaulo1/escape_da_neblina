#include "../include/no.h"
#include "../include/graph.h"
#include "../include/fila_prioridade.h"
#include "../include/dijkstra.h"

#include "stdio.h"
#include "stdlib.h"

#define INFINITO 0x3f3f3f3f

static void setarInfinito(double* vetor, int n)
{
	for(int i = 0; i < n; i++)
	{
		vetor[i] = INFINITO;
	}

	puts("Printar vetor infinito");

	for(int i = 0; i < n; i++)
	{
		printf("%lf ", vetor[i]);
	}

	puts("");
}

double* dijkstraPadrao(Grafo* g, int fonte) 
{
    	int n = quantidadeVertices(g);
    	Heap* heap = criarHeap(n);
    	Tupla vertice;
    	double* dist = (double*) malloc(n * sizeof(double));

    	for (int i = 0; i < n; i++) 
	{
        	dist[i] = INFINITO;
    	}

    	inserirNoHeap(heap, -0, fonte, 0, 0);
    	dist[fonte] = 0;

    	while (!empty(heap)) 
	{
        	vertice = removeNoHeap(heap);
        	int w = -vertice.d;
        	int u = vertice.v;

        	if (dist[u] < w) continue;

        	Lista* listaVizinhos = vizinhosVertice(g, u);
        	No* vizinho = listaVizinhos->primeiro;
        	while (vizinho != NULL) 
		{
            		int v = vizinho->vertice;
            		double n_w = vizinho->distancia;
            		if (dist[v] > w + n_w) 
			{
                		dist[v] = w + n_w;
                		inserirNoHeap(heap, -(w + n_w), v, 0, 0);
            		}

            		vizinho = vizinho->proximo;
        	}
    	}


    	puts("Vetor de distancias:");
	for(int i = 0; i < n; i++)
	{
		printf("%lf ", dist[i]);
	}	
	puts("SAINDO DA DIJKSTRA");
	
	destruirHeap(heap);

    	return dist;
}

double* dijkstra(Grafo* g, double energia, int num_portais, int fonte)
{
	int n = quantidadeVertices(g);
    	Heap* heap = criarHeap(n);
    	Tupla vertice;
    	double* dist = (double*) malloc(n * sizeof(double));
	int portais;

    	for (int i = 0; i < n; i++) 
	{
        	dist[i] = INFINITO;
    	}

    	inserirNoHeap(heap, 0, fonte,  num_portais, 0);
    	dist[fonte] = 0;

    	while (!empty(heap)) 
	{
        	vertice = removeNoHeap(heap);
        	int w = -vertice.d;
        	int u = vertice.v;
		int p = vertice.portais;

        	if (dist[u] < w) continue;

        	Lista* listaVizinhos = vizinhosVertice(g, u);
        	No* vizinho = listaVizinhos->primeiro;
        	while (vizinho != NULL) 
		{
            		int v = vizinho->vertice;
            		double n_w = vizinho->distancia;

            		if((dist[v] > w + n_w))
			{
				dist[v] = w + n_w;

				if(n_w == 0) 
				{
					if(p >= num_portais) 
					{
						vizinho = vizinho->proximo;
						continue;
					}

					portais = p + 1;
				}

				inserirNoHeap(heap, -(w + n_w), v, portais, 0);
				
			}
		
            		vizinho = vizinho->proximo;
        	}
    	}


    	puts("Vetor de distancias:");
	for(int i = 0; i < n; i++)
	{
		printf("%lf ", dist[i]);
	}	
	puts("SAINDO DA DIJKSTRA");
	
	destruirHeap(heap);

    	return dist;	
}


