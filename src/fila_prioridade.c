#include "../include/no.h"
#include "../include/fila_prioridade.h"

#include "stdio.h"
#include "stdlib.h"


Heap* criarHeap(int n)
{
	// Verifica se o parametro passado eh valido
	if(n < 1)
	{
	       	printf("Tamanho inválido!");
		
		return NULL;
	}
	
	Heap* heap = (Heap*) malloc(sizeof(Heap)); // Aloca dimanicamente o tamanho necessario para um 'Heap'
	Tupla* tuplas = (Tupla*) malloc(sizeof(Tupla) * (n)); // Aloca dinamicamente um vetor de tuplas 

	// Verifica se as alocacoes foram feitas corretamente
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
	if((a.h == 0) && (b.h == 0)) // Define que 'h' tem maior precedencia sobre os demais atributos 
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
	return (i - 1) / 2; // Na implementacao escolhida, o 'pai' do registro sempre  e obtido desta maneira
}

int getSucessorEsq(int i)
{
	return 2 * i + 1; // Na implementacao escolhida, o 'filho' da esquerda sempre eh obtido desta maneira
}

int getSucessorDir(int i)
{
    	return 2 * i + 2; // Na implementacao escolhida, o 'filho' da direita sempre  e obtido desta maneira
}

void destruirHeap(Heap* heap)
{
	free(heap->vetor); // Desaloca o vetor de Tuplas
	free(heap); // Desaloca o Heap
}


void inserirNoHeap(Heap* heap, double d, int v, int num_portais, double h)
{
	// Verifica se o Heap esta cheio
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

	// Procura a posicao correta para inserir o novo registro
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


Tupla removeNoHeap(Heap* heap) 
{
	if (heap->ocupados == 0) 
	{
        	printf("O heap está vazio!\n");
        	exit(1);
    	}

	// Pega a raiz (maior elemento) e a substitui pelo ultimo elemento do vetor 
    	Tupla raiz = heap->vetor[0];
    	Tupla ultimo = heap->vetor[heap->ocupados - 1];
    	heap->vetor[0] = ultimo;
    	heap->ocupados--;

    	int i = 0;

	// Faz o Heapfy
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
	// Retorna '1' se a lista estiver vazia e '0' caso contrario
	return (heap->ocupados == 0);
}
