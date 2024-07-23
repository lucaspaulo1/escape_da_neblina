/*
#include "./include/ponto.h"
#include "./include/no.h"
#include "./include/lista_encadeada.h"
#include "./include/graph.h"
#include "./include/grafo_matriz_adjacencia.h"
#include "./include/fila_prioridade.h"
#include "./include/encontrar_caminho.h"
#include "./include/testes.h"


#include "stdio.h"
#include "stdlib.h"

typedef enum
{
	LISTA_ADJ,
	MATRIZ_ADJ
} TipoGrafo; 


void writeData(FILE* file, TipoGrafo grafo, double en, int portais, int tam, int dij, int aes, double t_grafo, double t_dij, double t_aes, int dens)
{
    fprintf(file, "%d,%lf,%d,%d,%d,%d,%lf,%lf,%lf,%d", grafo, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}


void cabecalho(FILE *file)
{
         fprintf(file, "GRAFO,ENERGIA,PORTAIS,TAM,DIJ,AES,TIME_GRAFO,TIME_DIJ,TIME_AES,TIME_PROC,DENS\n");
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "stdbool.h"

const long int MAX_EDGES = 10000;
const long int MAX_PORTALS = 100000;

bool isTrailUnique(int trails[MAX_EDGES][2], int m, int u, int v) {
    for (int i = 0; i < m; ++i) {
        if (trails[i][0] == u && trails[i][1] == v) {
            return false;
        }
    }
    return true;
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

 // Função para calcular a diferença de tempo
void clkDiff(struct timespec start, struct timespec end, struct timespec* temp) 
{
      if ((end.tv_nsec - start.tv_nsec) < 0) {
          temp->tv_sec = end.tv_sec - start.tv_sec - 1;
          temp->tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
      } else {
          temp->tv_sec = end.tv_sec - start.tv_sec;
          temp->tv_nsec = end.tv_nsec - start.tv_nsec;
      }
 }


void generateRandomGraph(Grafo* g1, GrafoMatriz* g2, int n, bool isDense, double* energia, int* portais, double* heur, double* t1, double* t2) {
//	Grafo* g1 = NovoGrafo(); // EU// Cria um grafo de listas    
//	GrafoMatriz* g2 = criaMatriz(n); // EU // matriz 
	double distancias[n]; // EU 
	struct timespec inittp, endtp, restp; // EU // EU

	FILE *outfile = fopen("pqp", "w");
    if (outfile == NULL) {
        printf("Erro ao abrir o arquivo \n");
        exit(1);
    }


    double x[n], y[n];
    int trails[MAX_EDGES][2];
    int portals[MAX_PORTALS][2];
    int trailCount = 0;
    int portalCount = 0;

    // determinar a densidade e o número de arestas
    double density = isDense ? 0.7 : 0.3;
    int maxEdges = n * (n - 1);
    int m = (int)(density * maxEdges);

    // determinar a quantidade de portais
    int minPortals = 0;
    int maxPortals = (int)(0.3 * m);
    int k = minPortals + rand() % (maxPortals - minPortals + 1);
    m = m - k;

    fprintf(outfile, "%d %d %d\n", n, m, k);

    // determinar o número máximo de vezes que pode usar portais
    int minUses = 0;
    int maxUses = k;
    int q = minUses + rand() % (maxUses - minUses + 1);

    // gerar coordenadas aleatórias para cada clareira
    for (int i = 0; i < n; ++i) {
        x[i] = (double)rand() / RAND_MAX * 100.0;
        y[i] = (double)rand() / RAND_MAX * 100.0;
        fprintf(outfile, "%lf %lf\n", x[i], y[i]);

		insereVertice(g1); /// EU // Criar um vertice 'i'
    }

    // gerar trilhas aleatórias
    double totalTrailDistance = 0.0;
    while (trailCount < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && isTrailUnique(trails, trailCount, u, v)) {
            trails[trailCount][0] = u;
            trails[trailCount][1] = v;
            double dist = calculateDistance(x[u], y[u], x[v], y[v]);
            totalTrailDistance += dist;
            fprintf(outfile, "%d %d\n", u, v);

	    clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereArestaNaMatriz(g2, u, v, dist); // EU
		 clock_gettime(CLOCK_MONOTONIC, &endtp);
	 	*t2 = restp.tv_sec + (double) restp.tv_nsec; //T_AES

	    clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereAresta(g1, u, dist,v); // EU
	    clock_gettime(CLOCK_MONOTONIC, &endtp);
	   *t1 = restp.tv_sec + (double) restp.tv_nsec; //T_AES



            ++trailCount;
        }
    }

    // gerar portais aleatórios
    while (portalCount < k) {
        int u = rand() % n;
        int v = rand() % n;

        if (u != v && isTrailUnique(portals, portalCount, u, v)) {
            portals[portalCount][0] = u;
            portals[portalCount][1] = v;
            fprintf(outfile, "%d %d\n", u, v);
		
	   	 clock_gettime(CLOCK_MONOTONIC, &inittp);
         	insereArestaNaMatriz(g2, u, v, 0); // EU
		 clock_gettime(CLOCK_MONOTONIC, &endtp);
	 	*t2 = (*t2) + restp.tv_sec + (double) restp.tv_nsec; //T_AES


	  	clock_gettime(CLOCK_MONOTONIC, &inittp);
         	insereAresta(g1, u, 0,v); // EU
	 	clock_gettime(CLOCK_MONOTONIC, &endtp);
	 	*t1 = (*t1) + restp.tv_sec + (double) restp.tv_nsec; //T_AES

  	
            ++portalCount;
        }
    }

    // calcular energia com base na distância total
    double minEnergy = 0.1 * totalTrailDistance;
    double maxEnergy = 0.4 * totalTrailDistance;
    double s = minEnergy + ((double)rand() / RAND_MAX) * (maxEnergy - minEnergy);
	*energia = s;// EU
	*portais = q;// EU
	
	int saida = n - 1;
	for(int i = 0; i < n; i++) // EU // EU // EU 
	{
		double eisq1 = calculateDistance(x[i], y[i], x[saida], y[saida]);
		distancias[i] = eisq1;
	} // EU EUEUEU

	heur = distancias; // Eu
	printf("jeur: %lf ", heur[1]);

    fprintf(outfile, "%lf %d\n", s, q);

    fclose(outfile);
}

void executa(FILE* file, Grafo* g, TipoGrafo grafo, double en, int portais, int tam, double dens, double* heur, double t_grafo)
{
	struct timespec inittp, endtp, restp;
	double t_dij;
	double t_aes;
	int dij = 1;
	int aes = 0;
	int n = quantidadeVertices(g);

	 clock_gettime(CLOCK_MONOTONIC, &inittp);
         dijkstra(g, en, portais, 0); // alg
         clock_gettime(CLOCK_MONOTONIC, &endtp);
         clkDiff(inittp, endtp, &restp);
         t_dij = restp.tv_sec + (double) restp.tv_nsec; //T_DIJ

 		for(int i = 0; i < n; i++)
		{
			printf("%lf", heur[i]);
		}		
	 clock_gettime(CLOCK_MONOTONIC, &inittp);
         aEstrela(g, heur, en, portais, 0, tam - 1); // alg
         clock_gettime(CLOCK_MONOTONIC, &endtp);
	 t_aes = restp.tv_sec + (double) restp.tv_nsec; //T_AES

	writeData(file, LISTA_ADJ, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}

void executaMatriz(FILE* file, GrafoMatriz* g, TipoGrafo grafo, double en, int portais, int tam, double dens, double* heur, double t_grafo)
{
	struct timespec inittp, endtp, restp;
	double t_dij;
	double t_aes;
	int dij = 1;
	int aes = 0;

	 clock_gettime(CLOCK_MONOTONIC, &inittp);
         dijkstraMatriz(g, en, portais, 0); // alg
         clock_gettime(CLOCK_MONOTONIC, &endtp);
         clkDiff(inittp, endtp, &restp);
         t_dij = restp.tv_sec + (double) restp.tv_nsec; //T_DIJ
	
	 clock_gettime(CLOCK_MONOTONIC, &inittp);
         aEstrelaMatriz(g, heur, en, portais, 0, tam - 1); // alg
         clock_gettime(CLOCK_MONOTONIC, &endtp);
	 t_aes = restp.tv_sec + (double) restp.tv_nsec; //T_AES

	writeData(file, MATRIZ_ADJ, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}

void mensurarPerf(FILE* file, int max_size, Grafo* g1, GrafoMatriz* g2, double* energia, int* portais, int isDense)
{
	double* heur;
	double t_g1, t_g2;

	for(int i = 5; i < max_size; i = i + 5)
	{
		generateRandomGraph(g1, g2, i, isDense, energia, portais, heur, &t_g1, &t_g2);

		executa(file, g1, LISTA_ADJ, *energia, *portais, i, isDense, heur, t_g1);
		executaMatriz(file, g2, MATRIZ_ADJ, *energia, *portais, i, isDense, heur, t_g2);
	}
}

int main() 
{
    srand(time(0));

    int n = 50; // número de clareiras
    int isDense = 0;

	// EU     
    FILE* file = fopen("dados.csv", "w");
     if (file == NULL) {
         printf("Failed to open file\n");
         return 1;
     }
     
     cabecalho(file);
    Grafo* g1 = novoGrafo();
    GrafoMatriz* g2 = criaMatriz(n);
    double energia;
    int portais;
    int max_size = 200;

	

    mensurarPerf(file, max_size, g1, g2, &energia, &portais, isDense);
    //generateRandomGraph(g1, g2, n, isDense, &energia, &portais);
    printf("Arquivo gerado: ");

    return 0;
}

*/

#include "./include/ponto.h"
#include "./include/no.h"
#include "./include/lista_encadeada.h"
#include "./include/graph.h"
#include "./include/grafo_matriz_adjacencia.h"
#include "./include/fila_prioridade.h"
#include "./include/encontrar_caminho.h"
#include "./include/testes.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h> 

typedef enum {
    LISTA_ADJ,
    MATRIZ_ADJ
} TipoGrafo;

void writeData(FILE* file, TipoGrafo grafo, double en, int portais, int tam, int dij, int aes, double t_grafo, double t_dij, double t_aes,  int dens) {
    fprintf(file, "%d,%lf,%d,%d,%d,%d,%lf,%lf,%lf,%d\n", grafo, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}

void cabecalho(FILE *file) {
    fprintf(file, "GRAFO,ENERGIA,PORTAIS,TAM,DIJ,AES,TIME_GRAFO,TIME_DIJ,TIME_AES,DENS\n");
}

const long int MAX_EDGES = 10000;
const long int MAX_PORTALS = 100000;

bool isTrailUnique(int trails[MAX_EDGES][2], int m, int u, int v) {
    for (int i = 0; i < m; ++i) {
        if (trails[i][0] == u && trails[i][1] == v) {
            return false;
        }
    }
    return true;
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void clkDiff(struct timespec start, struct timespec end, struct timespec* temp) {
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp->tv_sec = end.tv_sec - start.tv_sec - 1;
        temp->tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp->tv_sec = end.tv_sec - start.tv_sec;
        temp->tv_nsec = end.tv_nsec - start.tv_nsec;
    }
}

void generateRandomGraph(Grafo* g1, GrafoMatriz* g2, int n, bool isDense, double* energia, int* portais, double** heur, double* t1, double* t2) {
    double* distancias = (double*)malloc(n * sizeof(double));
    struct timespec inittp, endtp, restp;

    FILE *outfile = fopen("pqp", "w");
    if (outfile == NULL) {
        printf("Erro ao abrir o arquivo \n");
        exit(1);
    }

    double x[n], y[n];
    int trails[MAX_EDGES][2];
    int portals[MAX_PORTALS][2];
    int trailCount = 0;
    int portalCount = 0;

    double density = isDense ? 0.7 : 0.3;
    int maxEdges = n * (n - 1);
    int m = (int)(density * maxEdges);

    int minPortals = 0;
    int maxPortals = (int)(0.3 * m);
    int k = minPortals + rand() % (maxPortals - minPortals + 1);
    m = m - k;

    fprintf(outfile, "%d %d %d\n", n, m, k);

    int minUses = 0;
    int maxUses = k;
    int q = minUses + rand() % (maxUses - minUses + 1);

    for (int i = 0; i < n; ++i) {
        x[i] = (double)rand() / RAND_MAX * 100.0;
        y[i] = (double)rand() / RAND_MAX * 100.0;
        fprintf(outfile, "%lf %lf\n", x[i], y[i]);
	
	clock_gettime(CLOCK_MONOTONIC, &inittp);
        insereVertice(g1); // adasd
	clock_gettime(CLOCK_MONOTONIC, &endtp);
        clkDiff(inittp, endtp, &restp);
        *t1 += restp.tv_sec + (double)restp.tv_nsec;
    }

    double totalTrailDistance = 0.0;
    while (trailCount < m) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && isTrailUnique(trails, trailCount, u, v)) {
            trails[trailCount][0] = u;
            trails[trailCount][1] = v;
            double dist = calculateDistance(x[u], y[u], x[v], y[v]);
            totalTrailDistance += dist;
            fprintf(outfile, "%d %d\n", u, v);

            clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereArestaNaMatriz(g2, u, v, dist);
            clock_gettime(CLOCK_MONOTONIC, &endtp);
            clkDiff(inittp, endtp, &restp);
            *t2 += restp.tv_sec + (double)restp.tv_nsec;

            clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereAresta(g1, u, dist, v);
            clock_gettime(CLOCK_MONOTONIC, &endtp);
            clkDiff(inittp, endtp, &restp);
            *t1 += restp.tv_sec + (double)restp.tv_nsec;
	

            ++trailCount;
        }
    }

    while (portalCount < k) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && isTrailUnique(portals, portalCount, u, v)) {
            portals[portalCount][0] = u;
            portals[portalCount][1] = v;
            fprintf(outfile, "%d %d\n", u, v);

            clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereArestaNaMatriz(g2, u, v, 0);
            clock_gettime(CLOCK_MONOTONIC, &endtp);
            clkDiff(inittp, endtp, &restp);
            *t2 += restp.tv_sec + (double)restp.tv_nsec / 1e9;

            clock_gettime(CLOCK_MONOTONIC, &inittp);
            insereAresta(g1, u, 0, v);
            clock_gettime(CLOCK_MONOTONIC, &endtp);
            clkDiff(inittp, endtp, &restp);
            *t1 += restp.tv_sec + (double)restp.tv_nsec / 1e9;

            ++portalCount;
        }
    }

    double minEnergy = 0.1 * totalTrailDistance;
    double maxEnergy = 0.4 * totalTrailDistance;
    double s = minEnergy + ((double)rand() / RAND_MAX) * (maxEnergy - minEnergy);
    *energia = s;
    *portais = q;

    int saida = n - 1;
    for (int i = 0; i < n; i++) {
        double eisq1 = calculateDistance(x[i], y[i], x[saida], y[saida]);
        distancias[i] = eisq1;
    }

    *heur = distancias;
    printf("heur[1]: %lf\n", (*heur)[1]);

    fprintf(outfile, "%lf %d\n", s, q);

    fclose(outfile);
}

void executa(FILE* file, Grafo* g, TipoGrafo grafo, double en, int portais, int tam, double dens, double* heur, double t_grafo) {
    struct timespec inittp, endtp, restp;
    double t_dij;
    double t_aes;
    int dij;
    int aes;
    int n = quantidadeVertices(g);
    double r;

    printf("executa: vertices %d\n", quantidadeVertices(g));
    clock_gettime(CLOCK_MONOTONIC, &inittp);
    r = dijkstra(g, en, portais, 0); // valor encontrado	
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_dij = restp.tv_sec + (double)restp.tv_nsec;// / 1e9;
    dij = ehPossivel(r, en); // resposta dij

    for (int i = 0; i < n; i++) {
        printf("%lf ", heur[i]);
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &inittp);
    r = aEstrela(g, heur, en, portais, 0, tam - 1);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_aes = restp.tv_sec + (double)restp.tv_nsec;// / 1e9;
    aes = ehPossivel(r, en);

    writeData(file, grafo, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}

void executaMatriz(FILE* file, GrafoMatriz* g, TipoGrafo grafo, double en, int portais, int tam, double dens, double* heur, double t_grafo) {
    struct timespec inittp, endtp, restp;
    double t_dij;
    double t_aes;
    int dij = 1;
    int aes = 0;
    int n = g->n;

    printf("executa: vertices %d\n", g->n);
    clock_gettime(CLOCK_MONOTONIC, &inittp);
    dijkstraMatriz(g, en, portais, 0);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_dij = restp.tv_sec + (double)restp.tv_nsec;

    for (int i = 0; i < n; i++) {
        printf("%lf ", heur[i]);
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &inittp);
    aEstrelaMatriz(g, heur, en, portais, 0, tam - 1);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_aes = restp.tv_sec + (double)restp.tv_nsec;// / 1e9;

    writeData(file, grafo, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}


void simular(int numTests, int n[], bool isDense, double* t1, double* t2) {
    FILE *file;
    srand(time(NULL));

    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    GrafoMatriz* g2 = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    double* heur = NULL;

    // 
    bool file_exists = access("dados_sim.csv", F_OK) != -1;
    file = fopen("dados_sim.csv", "a");
	if(file == NULL)
	{
		puts("DEU RUIM PARA CRIAR O GRAFICO");
		exit(1);
	}

	if (!file_exists) {
        	// Cabeçalho a ser impresso apenas na primeira vez
        	cabecalho(file);
    	}

    

    for (int i = 200; i < numTests; i = i + 5) 
    {
	if(i % 2 == 0) isDense = false;
	else
	{
		isDense = true;
	}

        double energia;
        int portais;
	
	Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    	GrafoMatriz* g2 = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    
	g = novoGrafo();
	g2 = criaMatriz(i);
	printf("%d\n\n", g2->n);

        generateRandomGraph(g, g2, i, isDense, &energia, &portais, &heur, t1, t2);
        executa(file, g, LISTA_ADJ, energia, portais, i, isDense, heur, *t1);
        executaMatriz(file, g2, MATRIZ_ADJ, energia, portais, i, isDense, heur, *t2);

	destroiMatriz(g2);
	deletaGrafo(g);
    }

    fclose(file);

    free(g);
    free(g2);
    free(heur);
}

int main() {
    int numTests = 350;
    int n[] = {100, 200, 300, 400, 500};
    double t1 = 0.0, t2 = 0.0;
    simular(numTests, n, true, &t1, &t2);
    
    return 0;
}

