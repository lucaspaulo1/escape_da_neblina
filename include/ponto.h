#ifndef PONTO_H
#define PONTO_H

/*
 * TAD que representa um ponto no plano cartesiano
 */
typedef struct
{
	double x; // Coordenada X
	double y; // Coordenada Y
} Ponto;

/*
 * Modifica os atributos de um Ponto
 */
void setPonto(Ponto* p, double a, double b);

/*
 * Retorna a coordenada x  do Ponto especificado
 */
double getXPonto(Ponto* p);

/*
 * Retorna a coordenad y do Ponto especificado
 */
double getYPonto(Ponto* p);

/*
 * Calcula e retorna a distancia euclidiana entre dois pontos
 */
double distanciaXY(Ponto p1, Ponto p2);


#endif
