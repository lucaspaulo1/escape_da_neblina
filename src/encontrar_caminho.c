#include "../include/no.h"
#include "../include/graph.h"
#include "../include/grafo_matriz_adjacencia.h"
#include "../include/fila_prioridade.h"
#include "../include/encontrar_caminho.h"

#include "stdio.h"
#include "stdlib.h"

void setarInfinito(double* vetor, int n)
{
	for(int i = 0; i < n; i++)
	{
		vetor[i] = INFINITO; // Constante 'INFINITO' foi definida no arquivo .h
	}
}

double dijkstra(Grafo* g, double energia, int num_portais, int fonte)
{
	int n = quantidadeVertices(g); // Quantidade de vertices do grafo
    	Heap* heap = criarHeap(n); // Quantidade de vertices do grafo
    	Tupla vertice; // Tupla representando os caminhos e vertices (clareiras) com os portais e heuristica
    	double* dist = (double*) malloc(n * sizeof(double)); // Vetor de distancias do vertice inicial a todo outro vertice do grafo
	int portais = 0; // Quantidade de portais usada
	double aux;
	int objetivo = n - 1;

	// Verifica a alocacao de memoria
	if(dist == NULL)
	{
		printf("A alocacao falhou para 'dist'!");
		exit(1);
	}

	setarInfinito(dist, n);

	// Colocar o vertice inicial no heap e atualizar a distancia dele para ele mesmo
    	inserirNoHeap(heap, 0, fonte,  0, 0);
    	dist[fonte] = 0;

	// Loop representando o processo de caminhar no grafo para encontrar a menor distancia para cada vertice
    	while (!empty(heap))
	{
        	vertice = removeNoHeap(heap); // Remove a raiz do Heap
        	double w = -vertice.d;
        	int u = vertice.v;
		int p = vertice.portais; // Representa o numero de portais do associado ao vertice no contexto do caminho

		if (u == objetivo) 
		{
			destruirHeap(heap);
			free(dist);
			return w;
		}

        	if (dist[u] < w) continue; // Verifica se o vertice ja foi visitado

        	Lista* listaVizinhos = vizinhosVertice(g, u);
        	No* vizinho = listaVizinhos->primeiro;

		// Itera sobre os vizinhos
        	while (vizinho != NULL)
		{
            		int v = vizinho->vertice;
            		double n_w = vizinho->distancia;

            		if((dist[v] > w + n_w)) // Verifica se o caminho atual eh o menor
			{
				aux = dist[v];
				dist[v] = w + n_w;

				if(n_w == 0) // Verifica se a aresta representa um portal
				{
					if(p >= num_portais) // Verifica se a quantidade de portais usadas no caminho eh valida
					{
						dist[v] = aux;
						vizinho = vizinho->proximo; // Se nao for, passe para o outro vizinho
						continue;
					}

					portais = p + 1; // Atualiza o numero de portais usados no caminho
				}

				inserirNoHeap(heap, -(w + n_w), v, portais, 0); // Insere no heap o vertice com sua distancia e quantidade de portais usados ate o momento

			}

            		vizinho = vizinho->proximo; // Passa para o proximo vizinho
        	}
    	}

	destruirHeap(heap); // Desaloca a memoria usada no heap
	free(dist);

    	return INFINITO;
}

double aEstrela(Grafo* grafo, double* heuristica, double energia, int num_portais, int fonte, int objetivo)
{
	int n = quantidadeVertices(grafo); // Quantidade de vertices do grafo
	Heap* fila = criarHeap(n); // Cria um Heap com 'n' espacos disponiveis
	Tupla vertice; // Tupla representando os caminhos e vertices (clareiras)
	double* caminho_fechado; // Caminho dos nos que serao usados pra calcular a menor distancia
	double aux;
	double g = 0; // Representa a distancia entre clareira passada e a atual (trilha)
	double h = 0; // Representa a heuristica do vertice atual
	double f = 0; // Representa a funcao de custo
	int portais = 0;
	
	caminho_fechado = (double*) malloc(sizeof(double) * n);
	
	// Verifica a alocacao de memoria
	if(caminho_fechado == NULL) 
	{
		printf("A alocacao falhou para 'caminho_fechado'!");
		exit(1);
	}

	setarInfinito(caminho_fechado, n);

	// Para a fonte (clareira inicial)
	inserirNoHeap(fila, -0, fonte, 0, 0);
	caminho_fechado[fonte] = 0;

	// Loop representando o processo de caminhar no grafo para encontrar a menor distancia para cada vertice
	while(!empty(fila))
	{
		// Remove a raiz do Heap e pega seus dados 
		vertice = removeNoHeap(fila);
		double w = -vertice.d;
		int u = vertice.v;
		int p = vertice.portais; 

		// Verifica se a saida e a entrada sao iguais
		if(u == objetivo) 
		{
			free(caminho_fechado);
			destruirHeap(fila);

			return w;
		}

		// Verifica se o 
		if(caminho_fechado[u] < w) continue;

		// Pega os vizinhos do vertice
		Lista* listaVizinhos = vizinhosVertice(grafo, u);
		No* vizinho = listaVizinhos->primeiro;

		// Itera sobre os vizinhos do vertice
		while(vizinho != NULL)
		{
			int v = vizinho->vertice;
			double n_w = vizinho->distancia;
			g = w + n_w; // Calcula o tamanho do caminho atual adicionado a distancia ate o vertice atual

			// Verifica se o caminho atual eh o menor
			if(caminho_fechado[v] > g)
			{
				aux = caminho_fechado[v];
				caminho_fechado[v] = g;
				h = heuristica[v]; // Pega a distancia em linha reta do vertice atual ate a saida
				f = (-g) + (-h); // Calcula a funcao de custo

				// Verifica se a aresta atual eh um portal
				if(n_w == 0)
				{
					if(p >= num_portais) // Verifica se a quantidade de portais usadas no caminho eh valida
					{
						caminho_fechado[v] = aux;
						vizinho = vizinho->proximo;
						continue;
					}

					portais = p + 1; // Atualiza a quantidade de portais usada
				}	

				inserirNoHeap(fila, -g, v, portais, f); // Insere no Heap a tupla com a funcao de custo calculada
			}

			vizinho = vizinho->proximo; // Pega o proximo vizinho
		}
	}

	destruirHeap(fila); // Desalaoca a memoria usada no Heap
	free(caminho_fechado);

	return INFINITO;
}

double dijkstraMatriz(GrafoMatriz* g, double energia, int num_portais, int fonte) 
{
    	int n = g->n; // Quantidade de vertices do grafo
    	Heap* heap = criarHeap(n); // Cria o heap
    	Tupla vertice; // Tupla representando os caminhos e vertices (clareiras) com os portais e heuristica
    	double* dist = (double*) malloc(n * sizeof(double)); // Vetor de distancias do vertice inicial a todo outro vertice do grafo
    	int portais = 0; // Quantidade de portais usada
    	double aux;
	int objetivo = n - 1;

    	// Verifica a alocacao de memoria
    	if (dist == NULL) 
	{
        	printf("A alocacao falhou para 'dist'!\n");
        	exit(1);
    	}

    	setarInfinito(dist, n);

    	// Colocar o vertice inicial no heap e atualizar a distancia dele para ele mesmo
    	inserirNoHeap(heap, 0, fonte, 0, 0);
    	dist[fonte] = 0;

    	// Loop representando o processo de caminhar no grafo para encontrar a menor distancia para cada vertice
    	while (!empty(heap)) 
	{
        	vertice = removeNoHeap(heap); // Remove a raiz do Heap
        	double w = -vertice.d;
        	int u = vertice.v;
        	int p = vertice.portais; // Representa o numero de portais do associado ao vertice no contexto do caminho

		if (u == objetivo) 
		{
			free(dist);
			destruirHeap(heap);

			
			return w;
		}

        	if (dist[u] < w) continue; // Verifica se o vertice ja foi visitado

        	// Itera sobre os vizinhos usando a matriz de adjacência
        	for (int v = 1; v < n; v++) 
		{
            		if (g->matriz[u][v].vertice == 1)  // Verifica se existe uma aresta entre u e v
			{
				double n_w = g->matriz[u][v].distancia;

                		if ((dist[v] > w + n_w)) // Verifica se o caminho atual eh o menor
                    		{
					aux = dist[v];
                    			dist[v] = w + n_w;

                    			if (n_w == 0) // Verifica se a aresta representa um portal
					{
						if (p >= num_portais)  // Verifica se a quantidade de portais usadas no caminho eh valida
						{
							dist[v] = aux;
                            				
							continue;
                        			}

                        			portais = p + 1; // Atualiza o numero de portais usados no caminho
                    			}
					else
					{
						portais = p;
					}
					
                    			inserirNoHeap(heap, -(w + n_w), v, portais, 0); // Insere no heap o vertice com sua distancia e quantidade de portais usados ate o momento
                		}
            		}
        	}
    	}

    	destruirHeap(heap); // Desaloca a memoria usada no heap
	free(dist);
    	
	return INFINITO;
}

double aEstrelaMatriz(GrafoMatriz* grafo, double* heuristica, double energia, int num_portais, int fonte, int objetivo) {
	int n = grafo->n; // Quantidade de vertices do grafo
    	Heap* fila = criarHeap(n); // Cria um Heap com 'n' espacos disponiveis
    	Tupla vertice; // Tupla representando os caminhos e vertices (clareiras)
    	double* caminho_fechado; // Caminho dos nos que serao usados pra calcular a menor distancia
    	double aux;
    	double g = 0; // Representa a distancia entre clareira passada e a atual (trilha)
    	double h = 0; // Representa a heuristica do vertice atual
    	double f = 0; // Representa a funcao de custo
    	int portais = 0;

    	caminho_fechado = (double*) malloc(sizeof(double) * n);

    	// Verifica a alocacao de memoria
    	if (caminho_fechado == NULL) 
	{
        	printf("A alocacao falhou para 'caminho_fechado'!\n");
        	exit(1);
    	}

	setarInfinito(caminho_fechado, n);

    	// Para a fonte (clareira inicial)
    	inserirNoHeap(fila, -0, fonte, 0, 0);
    	caminho_fechado[fonte] = 0;

    	// Loop representando o processo de caminhar no grafo para encontrar a menor distancia para cada vertice
    	while (!empty(fila)) {
        	// Remove a raiz do Heap e pega seus dados
        	vertice = removeNoHeap(fila);
        	double w = -vertice.d;
        	int u = vertice.v;
        	int p = vertice.portais;

        	// Verifica se a saida e a entrada sao iguais
        	if (u == objetivo)
		{
			free(caminho_fechado);
			destruirHeap(fila);

			return w;
		}

        	// Verifica se o
        	if (caminho_fechado[u] < w) continue;

        	// Itera sobre os vizinhos usando a matriz de adjacência
        	for (int v = 1; v < n; v++) {
            		if (grafo->matriz[u][v].vertice == 1) // Verifica se existe uma aresta entre u e v
			{
				double n_w = grafo->matriz[u][v].distancia;
               	 		g = w + n_w; // Calcula o tamanho do caminho atual adicionado a distancia ate o vertice atual

                		// Verifica se o caminho atual eh o menor            
				if (caminho_fechado[v] > g) 
				{
                    			aux = caminho_fechado[v];
                    			caminho_fechado[v] = g;
                    			h = heuristica[v]; // Pega a distancia em linha reta do vertice atual ate a saida
                    			f = (-g) + (-h); // Calcula a funcao de custo

                    			// Verifica se a aresta atual eh um portal
                    		if (n_w == 0) 
				{
                        		if (p >= num_portais) // Verifica se a quantidade de portais usadas no caminho eh valida
					{
						caminho_fechado[v] = aux;
                            		continue;
                        		}

                        		portais = p + 1; // Atualiza a quantidade de portais usada
                    		}
				else
				{
					portais = p;
				}

                    			inserirNoHeap(fila, -g, v, portais, f); // Insere no Heap a tupla com a funcao de custo calculada
                		}
            		}
        	}
    	}

    	destruirHeap(fila); // Desaloca a memoria usada no Heap
	free(caminho_fechado);

    	return INFINITO;
}

int ehPossivel(double distancia, double energia)
{
	if(distancia > energia) return 0;

	return 1;
}

int ehPossivelMatriz(double distancia, double energia) 
{
         if(distancia > energia) return 0;

         return 1;
}

void encontraCaminho(Grafo* g, int n, double energia, int num_portais, double* heuristica)
{
	int entrada = 0;
	int saida = n - 1;
	double menor_caminho_dijkstra = dijkstra(g, energia, num_portais, entrada);
	double menor_caminho_a_estrela = aEstrela(g, heuristica, energia, num_portais, entrada, saida);
	double resposta_dijkstra = menor_caminho_dijkstra;
	double resposta_a_estrela = menor_caminho_a_estrela;

	// Printa '1' caso Linque consiga escapar usando o Dijkstra e '0' caso contrario
	if(resposta_dijkstra <= energia) printf("1 ");
	else printf("0 ");

	// Printa '1' caso Linque consiga escapar usando o A* e '0' caso contrario
	if(resposta_a_estrela <= energia) printf("1 ");
	else printf("0\n");
}

void encontraCaminhoM(GrafoMatriz* g, int n, double energia, int num_portais, double* heuristica)
{
	int entrada = 0;
	int saida = n - 1;
	double menor_caminho_dijkstra = dijkstraMatriz(g, energia, num_portais, entrada);
	double menor_caminho_a_estrela = aEstrelaMatriz(g, heuristica, energia, num_portais, entrada, saida);
	double resposta_dijkstra = menor_caminho_dijkstra;
	double resposta_a_estrela = menor_caminho_a_estrela;

	// Printa '1' caso Linque consiga escapar usando o Dijkstra e '0' caso contrario
	if(resposta_dijkstra <= energia) printf("1 ");
	else printf("0");

	// Printa '1' caso Linque consiga escapar usando o A* e '0' caso contrario
	if(resposta_a_estrela <= energia) printf("1 ");
	else printf("0\n");
}


