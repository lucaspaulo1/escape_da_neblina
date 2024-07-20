#include "../include/no.h"
#include "../include/fila_prioridade.h"

#include "stdio.h"
#include "stdlib.h"

typedef struct
{
	int d;
	int v;
	int portais;
	int heuristica;
} Elemento;

/*

Heap* criarHeap(int n)
{
	Heap* heap = (Heap*) malloc(sizeof(Heap));
	Elemento* elemento = 
}


*/

Heap* criarHeap(int n)
{
	if(n < 1)
	{
	       	printf("Tamanho inválido!");
		
		return 0;
	}
	
	Heap* heap = (Heap*) malloc(sizeof(Heap));
	No* pares = (No*) malloc(sizeof(No) * (n + 2));

	if(heap == NULL || pares == NULL)
	{
		printf("A alocacao para o Heap falhou!");
		exit(1);
	}

	heap->tamanho = n;
	heap->ocupados = 0;
	heap->vetor = pares;

	return heap;
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

int compararNos(No a, No b)
{
	int v_a = getVertice(&a);
	int v_b = getVertice(&b);
	double d_a = getDistancia(&a);
	double d_b = getDistancia(&b);


    	if (d_a > d_b)
        	return 1;
    	if (d_a < d_b)
        	return -1;
    	if (v_a > v_b)
        	return 1;
  	if (v_a < v_b)
        	return -1;
   	 return 0;
}

void inserirNoHeap(Heap* heap, double d, int v)
{
	int i, pai, aux_v = 0;
	double aux_d = 0;
	No* pares = heap->vetor;

	if(heap->ocupados == heap->tamanho) 
	{
		printf("O heap está cheio!");

		exit(1);
	}

	setarNo(&pares[heap->ocupados], d, v);
	//heap->ocupados++;

	i = heap->ocupados;
	pai = getAncestral(i);
	
	while(compararNos(pares[i], pares[pai]) > 0)
	{
		// Troca pai pelo filho
		aux_d = getDistancia(&pares[pai]);
		aux_v = getVertice(&pares[pai]);
		setarNo(&pares[pai], getDistancia(&pares[i]), getVertice(&pares[i]));
	      	setarNo(&pares[i], aux_d, aux_v);

	
		// Atualiza os indices 
		i = pai;
		pai = (i - 1) / 2;
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

No removeNoHeap(Heap* heap)
{
    if (heap->ocupados == 0)
    {
        printf("O heap está vazio!\n");
        exit(1);
    }

    No raiz = heap->vetor[0];
    No ultimo = heap->vetor[heap->ocupados - 1];
    heap->vetor[0] = ultimo;
    heap->ocupados--;

    int i = 0;
    while (1)
    {
        int l = getSucessorEsq(i);
        int r = getSucessorDir(i);
        int maior = i;

        if (l < heap->ocupados &&
            (heap->vetor[l].distancia > heap->vetor[maior].distancia ||
             (heap->vetor[l].distancia == heap->vetor[maior].distancia && heap->vetor[l].vertice > heap->vetor[maior].vertice)))
        {
            maior = l;
        }

        if (r < heap->ocupados &&
            (heap->vetor[r].distancia > heap->vetor[maior].distancia ||
             (heap->vetor[r].distancia == heap->vetor[maior].distancia && heap->vetor[r].vertice > heap->vetor[maior].vertice)))
        {
            maior = r;
        }

        if (maior == i)
            break;

        No temp = heap->vetor[i];
        heap->vetor[i] = heap->vetor[maior];
        heap->vetor[maior] = temp;
        i = maior;
    }

    return raiz;
}


void imprimirHeap(Heap* heap)
{
	printf("\nImpressão do Heap (distancia, vertice):\n");
	for(int i = 0; i < heap->ocupados; i++)
	{
		printf("(%lf, %d)\n", heap->vetor[i].distancia, heap->vetor[i].vertice);
	}

	printf("\n");
}

int empty(Heap* heap)
{
	return (heap->ocupados == 0);
}
