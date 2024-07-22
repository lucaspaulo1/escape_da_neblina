#ifndef ENCONTRAR_CAMINHO_H
#define ENCONTRAR_CAMINHO_H

#define INFINITO 0x3f3f3f3f

/*
 * Seta 'INFINITO' para todos as posicoes do vetor
*/
void setarInfinito(double* vetor, int n);

/*
 * Calcula o caminhos mais curtos ate a saida da floresta usando o algoritmo Dijkstra.
 * @param 'g' representa o grafo com vertices e arestas (clareiras e trilhas).
 * @param 'energia' representa a quantidade de energia que Linque possui.
 * @param 'num_portais' representa o número máximo de portais que Linque pode usar.
 * @param 'fonte' representa a clareira inicial (sempre o vertice de indice 0).
*/
double* dijkstra(Grafo* g, double energia, int num_portais, int fonte);


/**
 * Calcula os caminhos mais curtos usando a saida da floresta usando o algoritmo A*.
 *
 * @param 'g' O grafo representando as clareiras e trilhas.
 * @param 'heuristica' Um vetor de distâncias (em linha reta) de cada clareira para a saida.
 * @param 'energia' A quantidade de energia que Linque possui.
 * @param 'num_portais' O número máximo de portais que Linque pode usar.
 * @param 'fonte' A clareira inicial (sempre 0).
 * @param 'objetivo' A clareira de saída (sempre n - 1).
 */
double* aEstrela(Grafo* g, double* heuristica, double energia, int num_portais, int fonte, int objetivo);


/*
 * Usa os dois algoritmos: Dijkstra e A* para verificar se Linque consegue escapar da floresta
 * 
*/
void encontraCaminho(Grafo* g, int n, double energia, int num_portais, double* heuristica);

#endif
