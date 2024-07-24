
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

/*
bool isTrailUnique(int trails[MAX_EDGES][2], int m, int u, int v) {

    	int loop = 0;

	puts("isTrail - inicio");

	for (int i = 0; i < m; ++i) {
        	//if (trails[i][0] == u && trails[i][1] == v) {
		if ((trails[i][0] == u && trails[i][1] == v) && (trails[i][0] == v && trails[i][1] == u))
    		{
	    	return false;
        	}

		loop = loop + 1;
    	}

	printf("loop: %d\n", loop);
	puts("isTrail - fim");
    return true;
}
*/

int isTrailUnique(int trails[][2], int trailCount, int u, int v) {
    
	puts("entrou nessa pora");
	for (int i = 0; i < trailCount; i++) {
        if ((trails[i][0] == u && trails[i][1] == v) || (trails[i][0] == v && trails[i][1] == u)) {
            return 0;
        }
    }
    
    puts("saiu dessa porra");
    return 1;
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

void lerGrafos(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    int n, m;
    while (fscanf(file, "%d %d\n", &n, &m) != EOF) {
        printf("Grafo com %d vértices e %d arestas:\n", n, m);

        for (int i = 0; i < m; i++) {
            int u, v;
            double peso;
            fscanf(file, "%d %d %lf\n", &u, &v, &peso);
            printf("Aresta: %d-%d com peso %lf\n", u, v, peso);
        }

        // Ler e ignorar o caractere especial de final
        char end_marker[6];
        fgets(end_marker, sizeof(end_marker), file);
        if (strcmp(end_marker, "#END#\n") != 0) {
            printf("Erro: formato do arquivo inválido.\n");
            break;
        }
    }

    fclose(file);
}

void generateRandomGraph(Grafo* g1, GrafoMatriz* g2, int n, bool isDense, double* energia, int* portais, double** heur, double* t1, double* t2) {
    double* distancias = (double*)malloc(n * sizeof(double));
    struct timespec inittp, endtp, restp;

    double x[n], y[n];
    int trails[MAX_EDGES][2];
    int portals[MAX_PORTALS][2];
    int trailCount = 0;
    int portalCount = 0;


    for (int i = 0; i < MAX_EDGES; i++) {
    trails[i][0] = -1;
    trails[i][1] = -2;
}

for (int i = 0; i < MAX_PORTALS; i++) {
    portals[i][0] = -1;
    portals[i][1] = -2;
}

    double density = isDense ? 0.7 : 0.1;
    int maxEdges = n * (n - 1);
    int m = (int)(density * maxEdges);

    int minPortals = 0;
    int maxPortals = (int)(0.3 * m);
    int k = minPortals + rand() % (maxPortals - minPortals + 1);
    m = m - k;

    int minUses = 0;
    int maxUses = k;
    int q = minUses + rand() % (maxUses - minUses + 1);

    for (int i = 0; i < n; ++i) {
        x[i] = (double)rand() / RAND_MAX * 100.0;
        y[i] = (double)rand() / RAND_MAX * 100.0;
	
	clock_gettime(CLOCK_MONOTONIC, &inittp);
        insereVertice(g1); // adasd
	clock_gettime(CLOCK_MONOTONIC, &endtp);
        clkDiff(inittp, endtp, &restp);
        *t1 += restp.tv_sec + (double)restp.tv_nsec;
    }

    double totalTrailDistance = 0.0;

    puts("lp1");

puts("lp1");
while (trailCount < m) {
    int u = rand() % n;
    int v = rand() % n;
	
    printf("u e v: %d %d", u, v);
    if (u != v && !isTrailUnique(trails, trailCount, u, v)) 
    {
    	while(!isTrailUnique(trails, trailCount, u, v))
	{
		v = u + 1;
		u = u - 1;
		if(v >= n) v = u - 2;
		if(u >= n) u = 2;
		if(v == 0) v = n - 2;
		if(u == 0) u = n - 2;
	}
    }
    else
    {
	printf("u e v: %d %d", u, v);
	trails[trailCount][0] = u;
        trails[trailCount][1] = v;
        double dist = calculateDistance(x[u], y[u], x[v], y[v]);
        totalTrailDistance += dist;

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

puts("lp2");
while (portalCount < k) {
    int u = rand() % n;
    int v = rand() % n;

    printf("portal u e v: %d %d", u, v);
    if (u != v && !isTrailUnique(portals, portalCount, u, v)) 
    {
       	while(!isTrailUnique(trails, trailCount, u, v))
	{
		v = u + 1;
		u = u - 1;
		if(v >= 1) v = u - 2;
	}
    }
    else
    {
	printf("u e v: %d %d", u, v);
	trails[trailCount][0] = u;
        trails[trailCount][1] = v;
        double dist = calculateDistance(x[u], y[u], x[v], y[v]);
        totalTrailDistance += dist;

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
	printf("DIjkstra %d\n:", dij);

    clock_gettime(CLOCK_MONOTONIC, &inittp);
    r = aEstrela(g, heur, en, portais, 0, tam - 1);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_aes = restp.tv_sec + (double)restp.tv_nsec;// / 1e9;
    aes = ehPossivel(r, en);
	printf("A* %d\n:", aes);

    writeData(file, grafo, en, portais, tam, dij, aes, t_grafo, t_dij, t_aes, dens);
}

void executaMatriz(FILE* file, GrafoMatriz* g, TipoGrafo grafo, double en, int portais, int tam, double dens, double* heur, double t_grafo) {
    struct timespec inittp, endtp, restp;
    double t_dij;
    double t_aes;
    int dij = 0;
    int aes = 0;
    int n = g->n;
    double r = 0;

    clock_gettime(CLOCK_MONOTONIC, &inittp);
    r = dijkstraMatriz(g, en, portais, 0);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_dij = restp.tv_sec + (double)restp.tv_nsec;

	dij = ehPossivelMatriz(r, en);
	printf("DIjkstraMATRIZ %d\n:", dij);

    clock_gettime(CLOCK_MONOTONIC, &inittp);
    aEstrelaMatriz(g, heur, en, portais, 0, tam - 1);
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);
    t_aes = restp.tv_sec + (double)restp.tv_nsec;// / 1e9;
	aes = ehPossivelMatriz(r, en);
	printf("A*MATRIZ %d\n:", aes);

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

    

    for (int i = 5; i < numTests; i = i + 5) 
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
	puts("gerou?");
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
    int numTests = 200;
    int n[] = {100, 200, 300, 400, 500};
    double t1 = 0.0, t2 = 0.0;
    simular(numTests, n, true, &t1, &t2);
    
    return 0;
}

