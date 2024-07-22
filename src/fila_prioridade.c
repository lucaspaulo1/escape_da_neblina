#include "../include/no.h"
#include "../include/fila_prioridade.h"

#include "stdio.h"
#include "stdlib.h"


Heap* criarHeap(int n)
{
	if(n < 1)
	{
	       	printf("Tamanho inválido!");
		
		return 0;
	}
	
	Heap* heap = (Heap*) malloc(sizeof(Heap));
	Tupla* tuplas = (Tupla*) malloc(sizeof(Tupla) * (n));

	if(heap == NULL || tuplas == NULL)
	{
		printf("A alocacao para o Heap falhou!");
		exit(1);
	}

	heap->tamanho = n;
	heap->ocupados = 0;
	heap->vetor = tuplas;

	return heap;
}

void setTupla(Tupla* tupla, double dist, int vert, int port, double hstc)
{
	tupla->d = dist;
	tupla->v = vert;
	tupla->portais = port;
	tupla->h = hstc;
}

int compararTuplas(Tupla a, Tupla b)
{
	if((a.h == 0) && (b.h == 0))
	{
    		if (a.d > b.d) return 1;
    		if (a.d < b.d) return -1;
    		if (a.v > b.v) return 1;
    		if (a.v < b.v) return -1;
	}
	else
	{
		if(a.h > b.h) return 1;
		if(a.h < b.h) return -1;
		if(a.d > b.d) return 1;
		if(a.d < b.d) return -1;
		if(a.v > b.v) return 1;
		if(a.v < b.v) return -1;
	}
    
	return 0;
}

int getAncestral(int i)
{
	return (i - 1) / 2;
}

int getSucessorEsq(int i)
{
	return 2 * i + 1;
}

int getSucessorDir(int i)
{
    	return 2 * i + 2;
}

void destruirHeap(Heap* heap)
{
	free(heap->vetor);
	free(heap);
}


void inserirNoHeap(Heap* heap, double d, int v, int num_portais, double h)
{
    	if (heap->ocupados == heap->tamanho) 
	{
        	printf("O heap está cheio!");
        	exit(1);
    	}

    	Tupla novaTupla;
    	setTupla(&novaTupla, d, v, num_portais, h);
    	heap->vetor[heap->ocupados] = novaTupla;

    	int i = heap->ocupados;
    	int pai = getAncestral(i);

    	while (i > 0 && compararTuplas(heap->vetor[i], heap->vetor[pai]) > 0) 
	{
        	Tupla temp = heap->vetor[i];
        	heap->vetor[i] = heap->vetor[pai];
        	heap->vetor[pai] = temp;

        	i = pai;
        	pai = getAncestral(i);
    	}

    	heap->ocupados++;
}

/*
No* removeNoHeap(Heap* heap)
{
	int i_ultimo = (heap->ocupados) - 1;
	int i, l, r, filho, aux_v = 0;
	double aux_d = 0;
	No* pares = heap->vetor;
	No primeiro = pares[0];
	No ultimo = pares[i_ultimo];
	No* raiz;

	if(heap->ocupados == 0) 
	{
		printf("O heap está vazio!");
		exit(1);
	}

	// Pega a raiz
	setarNo(raiz, primeiro.distancia, primeiro.vertice);
	
	//Troca raiz pelo ultimo elemento do Heap
	setarNo(&primeiro, ultimo.distancia, ultimo.vertice);

	// Decrementa a quantidade de elementos do Heap
	heap->ocupados--;
	
	// Define os indices
	i = 0;
	l = GetSucessorEsq(i);
	r = GetSucessorDir(i);

	// 's' recebe o maior sucessor de 'i'
	filho = l;
	if(l < r) filho = r;

	// Faz o Heapify caso necessario
	while(compararNos(pares[filho], pares[i]) > 0)
	{
		// Troca filho pelo pai
		aux_d = getDistancia(pares[filho]);
 	       	aux_v = getVertice(pares[filho]);
                setarNo(&pares[filho], getDistancia(&pares[i]), getVertice(&pares[i]));
                setarNo(&pares[i], aux_d, aux_v);


		// Define os indices
		i = filho;
		filho = l;
		if(l < r) filho = r;
	}

	return raiz;
}
*/

Tupla removeNoHeap(Heap* heap) 
{
	if (heap->ocupados == 0) 
	{
        	printf("O heap está vazio!\n");
        	exit(1);
    	}

    	Tupla raiz = heap->vetor[0];
    	Tupla ultimo = heap->vetor[heap->ocupados - 1];
    	heap->vetor[0] = ultimo;
    	heap->ocupados--;

    	int i = 0;
    	while (1) 
	{
        	int l = getSucessorEsq(i);
        	int r = getSucessorDir(i);
        	int maior = i;

		// Verifica se o filho eh maior que o pai
        	if (l < heap->ocupados && compararTuplas(heap->vetor[l], heap->vetor[maior]) > 0) 
		{
            		maior = l;
        	}

		// Verifica se o filho eh maior que o pai
        	if (r < heap->ocupados && compararTuplas(heap->vetor[r], heap->vetor[maior]) > 0) 
		{
        		maior = r;
        	}

       	 	if (maior == i)
            		break;

        	Tupla temp = heap->vetor[i];
        	heap->vetor[i] = heap->vetor[maior];
        	heap->vetor[maior] = temp;
        	i = maior;
    	}

    	return raiz;
}


void imprimirHeap(Heap* heap)
{
	Tupla* t = heap->vetor;
	printf("\nImpressão do Heap (distancia, vertice, quantidade de portais, heuristica):\n");
	for(int i = 0; i < heap->ocupados; i++)
	{
		printf("(%lf, %d, %d, %lf)\n", t[i].d, t[i].v, t[i].portais, t[i].h);
	}

	printf("\n");
}

int empty(Heap* heap)
{
	return (heap->ocupados == 0);
}
