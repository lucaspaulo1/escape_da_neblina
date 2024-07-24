#include "../include/ponto.h"
#include "../include/no.h"
#include "../include/lista_encadeada.h"
#include "../include/graph.h"
#include "../include/grafo_matriz_adjacencia.h"
#include "../include/fila_prioridade.h"
#include "../include/encontrar_caminho.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX 100000
#define INF 0x3f3f3f3f 

void testeHeap()
{
	int n = 0;
	printf("Teste no heap\n");

	printf("Insira a quantidade de elementos no Heap: ");
	scanf("%d", &n);
	n = 5;

	Heap* heap = criarHeap(n);
	inserirNoHeap(heap, 10, 5, 0, 0);
	inserirNoHeap(heap, 2, 6, 0, 0);
	inserirNoHeap(heap, 1, 1, 0, 0);
	inserirNoHeap(heap, 10, 6, 0, 0);
	inserirNoHeap(heap, -1, 48, 0, 0);

	Heap* heap2 = criarHeap(7);
	inserirNoHeap(heap2, 23, 0, 0, 0);
	inserirNoHeap(heap2, 21, 0, 0, 0);
	inserirNoHeap(heap2, 9, 0, 0, 0);
	inserirNoHeap(heap2, 13, 0, 0, 0);
	inserirNoHeap(heap2, 15, 0, 0, 0);
	inserirNoHeap(heap2, 8, 0, 0, 0);
	inserirNoHeap(heap2, 2, 0, 0, 0);

	Heap* heap3 = criarHeap(3);
	inserirNoHeap(heap3, 5, 10, 0, 0);
	inserirNoHeap(heap3, 10, 3, 0, 0);
	inserirNoHeap(heap3, 5, -1, 0, 0);

	Heap* heap4 = criarHeap(3);
	inserirNoHeap(heap4, -15, 10, 0, 0);
      	inserirNoHeap(heap4, -10, 3, 0, 0);
      	inserirNoHeap(heap4, -1, -1, 0, 0);

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
		Tupla raiz = removeNoHeap(heap2);

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

int min(int a, int b)
{
	if(a > b) return b; 

	return a;
}

void testeDijkstra()
{
	Grafo* g = novoGrafo();

	int n = 8;
	int energia = 5;
	int portais = 2;
	int saida = n - 1;

	for(int i = 0; i < n; i++)
	{
		insereVertice(g);
	}

	insereAresta(g, 0, 0, 1);
	insereAresta(g, 0, 2, 2);
	insereAresta(g, 0, 3, 3);
	insereAresta(g, 1, 0, 4);
	insereAresta(g, 2, 4, 7);
	insereAresta(g, 3, 1, 5);
	insereAresta(g, 4, 0, 7);
	insereAresta(g, 5, 0, 6);
	insereAresta(g, 6, 1, 7);
	
	imprimeGrafo(g);

	double dist = dijkstra(g, energia, portais, 0);

	puts("");
	puts("");

	printf("distancia ate a saida: %lf\n\n", dist);


	Grafo* g2 = novoGrafo();
	n = 7;
	saida = n - 1;
	energia = 10;
	portais = 2;

	for(int i = 0; i < n; i++) insereVertice(g2);

	insereAresta(g2, 0, 0, 1);
       	insereAresta(g2, 1, 0, 2);
	insereAresta(g2, 1, 0, 3);
	insereAresta(g2, 2, 1, 4);
	insereAresta(g2, 2, 0, 5);
	insereAresta(g2, 3, 3, 6);
	insereAresta(g2, 4, 1, 6);
	insereAresta(g2, 5, 1, 6);

	imprimeGrafo(g2);

	double dist2 = dijkstra(g2, energia, portais, 0);
	printf("distancia ate a saida: %lf\n\n", dist2);

	Grafo* g3 = novoGrafo();
	n = 4;
	saida = n - 1;
	energia = 5;
	portais = 0;
	for(int i = 0; i < n; i++) insereVertice(g3);

	insereAresta(g3, 0, 0, 1);
	insereAresta(g3, 0, 1, 2);
      	insereAresta(g3, 1, 1, 3);
	insereAresta(g3, 2, 1, 1);
	insereAresta(g3, 2, 4, 3);

	imprimeGrafo(g3);
	double dist3 = dijkstra(g3, energia, portais, 0);
       	printf("distancia ate a saida: %lf\n\n", dist3);	

}

void testeMatriz()
{
	int k = 5;
	GrafoMatriz* g = criaMatriz(k);
	int m = g->n;

	printf("m: %d\n", m);
	for(int i = 0; i < k; i++);

	// vertice, vertice, distancia
	insereArestaNaMatriz(g, 0, 1, 1);
       	insereArestaNaMatriz(g, 0, 2, 0);
	insereArestaNaMatriz(g,	0, 3, 1);
	insereArestaNaMatriz(g, 1, 4, 10.198);
	insereArestaNaMatriz(g, 2, 4, 10);
	insereArestaNaMatriz(g, 3, 4, 0);

	imprimeMatriz(g);
	destroiMatriz(g);
}

/*
void testeSorvete()
{
	puts("entrou na funcao");

	int N, M, X;
	scanf("%d %d %d", &N, &M, &X);

	Grafo* grp = novoGrafo();

	puts("A");
	for(int i = 0; i < N; i++)
		insereVertice(grp);

	puts("B");
	int a, b, w;
	for(int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &a, &b, &w);
		a--;
		b--;
		insereAresta(grp, a, w, b);
		insereAresta(grp, b, w, a);
	}

	puts("C");
	int* friends = (int*) malloc(sizeof(int) * X);
	for(int i = 0; i < X; i++)
		scanf("%d", &friends[i]);

	
	puts("D");
	double* dist_to_friends = dijkstraPadrao(grp, 0);
	double* dist_to_icecream = dijkstraPadrao(grp, N-1);
	
	puts("E");
	int ans = INF;
	for(int i = 0; i < X; i++)
	{
		int fr = friends[i];
		int w = (int) dist_to_friends[fr-1] + dist_to_icecream[fr-1];
		ans = min(ans, w);
	}
	
	puts("");
	printf("Problema do sorvete: %d\n", ans);

	free(friends);	
	free(dist_to_friends);
	free(dist_to_icecream);
	
	imprimeGrafo(grp);
	deletaGrafo(grp);
}




*/
