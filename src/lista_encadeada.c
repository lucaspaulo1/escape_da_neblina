#include "../include/lista_encadeada.h"

#include <stdio.h>
#include <stdlib.h>

Lista* criarLista(int idVertice)
{
	Lista* lista = (Lista*) malloc(sizeof(Lista)); // Aloca dinamicamente a memoria na pilha
	lista->primeiro = NULL;
	lista->ultimo = NULL;
	lista->proximaLista = NULL;
	lista->vertices = 0;
	lista->item = idVertice;

	return lista;
}

int getTamanhoLista(Lista* l)
{
	return l->vertices;
}

int listaVazia(Lista* l)
{
	return l->primeiro == NULL;
}

No* get(Lista* l, int v)
{
	No* aux = l->primeiro;

	// Itera sobre a lista "pulando" para o proximo No 
	while(aux != NULL)
	{
		if(aux->vertice == v)
		{
			return aux;
		}
		else
		{
			aux = aux->proximo;
		}
	}

	return NULL;
}

void insereFinal(Lista* l, double d, int v)
{
	No* no = criarNo(d, v);
	
	// Verifica se a lista esta vazia
	if(listaVazia(l))
	{
		l->primeiro = no;
		l->ultimo = no;
		l->vertices++;
	}
	else
	{
		l->ultimo->proximo = no;
		l->ultimo = no;
		l->vertices++;
	}
}

void removeFinal(Lista* l)
{
	// Verifica se a lista esta vazia
	if(l->primeiro == NULL)
	{
		printf("\nLista vazia!\n");
	}
	else
	{
		// Verifica se a lista tem exatamente um No (vertice)
		if(l->vertices == 1)
		{
			free(l->primeiro);
			l->primeiro = NULL;
			l->ultimo = NULL;
		}
		else
		{
			No* aux = l->primeiro;

			while(aux->proximo->proximo != NULL)
			{
				aux = aux->proximo;
			}

			free(aux->proximo);
			aux->proximo = NULL;
			l->ultimo = aux;
		}
	}
	l->vertices--;
}

void imprimirLista(Lista* l)
{
	No* aux = l->primeiro;

	while(aux != NULL)
	{
		//printf("%d\t", aux->vertice);
		imprimirNo(aux);

		aux = aux->proximo;
	}

	printf("\n");
}

void destruirLista(Lista* l)
{
	// Enquanto a lista nao estiver vazia, remove cada No um por um
	while(!listaVazia(l))
	{
		removeFinal(l);
	}

	free(l);
}


