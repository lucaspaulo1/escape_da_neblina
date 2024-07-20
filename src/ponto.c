#include "../include/ponto.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

void setPonto(Ponto* p, double a, double b)
{
	p->x = a;
	p->y = b;
}

double getXPonto(Ponto* p)
{
	return p->x;
}

double getYPonto(Ponto* p)
{
	return p->y;
}

double distanciaXY(Ponto p1, Ponto p2)
{
	double a = p2.x - p1.x;
	double b = p2.y - p2.y;
	double h = pow(a, 2) + pow(b, 2);

	return sqrt(h);
}
