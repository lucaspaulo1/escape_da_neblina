#include "../include/no.h"

#include <stdio.h>
#include <stdlib.h>


// Sem muitos comentarios pois os codigos sao muito simples

No* criarNo(double d, int v)
{
	No* novo_no = (No*) malloc(sizeof(No)); // Aloca dinamicamente memoria para um No na pilha
	novo_no->distancia = d;
	novo_no->vertice = v;
	novo_no->proximo = NULL; // Define o proximo No como nulo (para evitar um lixo)

	return novo_no;
}

double getDistancia(No* no)
{
	return no->distancia;
}

int getVertice(No* no)
{
	return no->vertice;
}

void setarNo(No* no, double d, int v)
{
        no->distancia = d;
        no->vertice = v;
}

void imprimirNo(No* no)
{
	printf("(%lf, %d)", no->distancia, no->vertice);
}
