#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include "./no.h"

/*
 * TAD representando uma lista de adjacencia adaptada para que cada lista representa os vizinhos de um vertice
 */
typedef struct lista
{
	int vertices;
	int item;
	No* primeiro;
	No* ultimo;
	struct lista* proximaLista;
} Lista;

/*
 * Cria uma nova lista encadeada com um id associado
 */
Lista* criarLista(int idVertice);

/*
 * Retorna o tamanho da lista
 */
int getTamanhoLista(Lista* l);

/*
 * Verifica se a lista esta vazia
 */
int listaVazia(Lista* l);

/*
 * Retorna um No(vertice) especifico 
 */
No* get(Lista* l, int v);

/*
 * Adiciona um novo No na lista colocando o no final
 */
void insereFinal(Lista* l, double d, int v);

/*
 * Remove o no final da lista
 */
void removeFinal(Lista* l);

/*
 * Imprime a lista
 */
void imprimirLista(Lista* l);

/*
 * Destroi a lista desalocando toda memoria
 */
void destruirLista(Lista* l);



#endif
