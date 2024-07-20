#include "../include/ponto.h"
#include "../include/no.h"
#include "../include/lista_encadeada.h"
#include "../include/graph.h"
#include "../include/fila_prioridade.h"
#include "../include/dijkstra.h"


#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX 100000

void testeHeap()
{
	int n = 0;
	printf("Teste no heap\n");

	printf("Insira a quantidade de elementos no Heap: ");
	scanf("%d", &n);
	n = 5;

	Heap* heap = criarHeap(n);
	inserirNoHeap(heap, 10, 5);
	inserirNoHeap(heap, 2, 6);
	inserirNoHeap(heap, 1, 1);
	inserirNoHeap(heap, 10, 6);
	inserirNoHeap(heap, -1, 48);

	Heap* heap2 = criarHeap(7);
	inserirNoHeap(heap2, 23, 0);
	inserirNoHeap(heap2, 21, 0);
	inserirNoHeap(heap2, 9, 0);
	inserirNoHeap(heap2, 13, 0);
	inserirNoHeap(heap2, 15, 0);
	inserirNoHeap(heap2, 8, 0);
	inserirNoHeap(heap2, 2, 0);

	Heap* heap3 = criarHeap(3);
	inserirNoHeap(heap3, 5, 10);
	inserirNoHeap(heap3, 10, 3);
	inserirNoHeap(heap3, 5, -1);

	Heap* heap4 = criarHeap(3);
	inserirNoHeap(heap4, -15, 10);
      	inserirNoHeap(heap4, -10, 3);
      	inserirNoHeap(heap4, -1, -1);

	puts("heap1:");
	imprimirHeap(heap);

	puts("heap2");
	imprimirHeap(heap2);

	puts("heap3");
	imprimirHeap(heap3);

	puts("heap4");
	imprimirHeap(heap4);

	puts("heap2 - remocao");
	while(!empty(heap2))
	{
		No raiz = removeNoHeap(heap2);

		imprimirHeap(heap2);
	}

	puts("destuir heaps");
	destruirHeap(heap);
	destruirHeap(heap2);
	destruirHeap(heap3);
	destruirHeap(heap4);	
}

void testeVertices()
{
	int n, v, e;
	puts("Teste grafos\n"); 
	puts("Passos: 1- inserir vertices\n 2- imprimir grafo\n 3- Inserir arestas\n 4- imprimir grafo\n 5- deletar grafo\n 6- imprimir grafoi\n ");

	printf("digite a quantidade de vertices: ");
	scanf("%d", &n);
	Grafo* g = novoGrafo();
	n = 5;

	for(int i = 0; i < n; i++)
	{
		insereVertice(g);
	}

	puts("Passo 2 - Imprimir grafo");
	imprimeGrafo(g);

	puts("Passo 3 - Inserir arestas");
	insereAresta(g, 0, 1, 1);
	insereAresta(g, 0, 0, 2);
	insereAresta(g, 0, 1, 3);
	insereAresta(g, 1, 10.198, 4);
	insereAresta(g, 2, 10, 4);
	insereAresta(g, 3, 0, 4);

	puts("Passo 4 - Imprimir grafo");
	imprimeGrafo(g);

	puts("Passo 5 - Deletar grafo");
	deletaGrafo(g);	
}

void testeGrafo(Grafo* g)
{
	return ;
}

void testeListas(Grafo* g) {
    puts("entrou na teste listas");
    int n = quantidadeVertices(g);
    Lista* eisque;
    No* aux;

    puts("Testa da funcao vizinhos");
    for (int i = 0; i < n; i++) {
        eisque = vizinhosVertice(g, i);
        if (eisque == NULL) {
            printf("Nao foi possivel encontrar a lista de adjacencia para o vertice %d\n", i);
            continue;
        }

        puts("deu certo pegar a lista?");
        if (eisque->primeiro == NULL) {
            printf("A lista de adjacencia para o vertice %d esta vazia\n", i);
            continue;
        }

        aux = eisque->primeiro;
        puts("deu certo pegar o primeiro no da lista?");
        printf("NO pai: %d Filhos: ", i);

        while (aux != NULL) {
            printf("%d ", aux->vertice);
            aux = aux->proximo;
        }

        puts("");
    }
}
