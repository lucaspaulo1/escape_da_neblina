#include <bits/stdc++.h>
#define f first
#define s second
#define _ ios::sync_with_stdio(0);cin.tie(0);

#include <iostream>
#include <algorithm> 
#include <queue>
#include <utility>

#include "./include/no.h"
#include "./include/fila_prioridade.h"

using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, q;

typedef pair<int, int> Aresta;
typedef vector< vector<Aresta> > Grafo;

void comparaVetor(vector<int> vetor1, vector<int> vetor2)
{

	if (vetor1 == vetor2) {
        std::cout << "Os vetores são iguais. tamanho: " << vetor1.size() << std::endl;
    } else {
        std::cout << "Os vetores são diferentes. tamanho: " << vetor2.size() << std::endl;
    }

	cout << "elementos:" << endl;
	for (int i = 0; i < vetor2.size(); ++i) {
        	std::cout << vetor2[i] << ' ';
    	}

}

vector<int> dijkstra(Grafo &g, vector<int> vertices)
{
	priority_queue< Aresta > fila;

	for(int v : vertices)
	{
		fila.push({-0, v - 1}); // Caso dele onde os vertices sao dados de 1 ate n ?				
	}

	vector<int> dist(n, INF);

	while(fila.empty() != 1) //Enquanto a fila nao estiver vazia
	{
		int w = -fila.top().f;
		int u = fila.top().s;
		fila.pop();

		if(dist[u] <= w) continue;

		/*
		if(u == destino) 
		{
			dist[0] = w;
			return dist; // Distancia ate um vertice especifico
		}
		*/

		dist[u] = w;
		for(auto [v, n_w]: g[u])
		{
			if(dist[v] > w + n_w) fila.push({-(w + n_w), v});
		}
	}

	return dist;
}

vector<int> dijkstraOne(Grafo &g, int source) {
    priority_queue<Aresta> fila;
    vector<int> dist(g.size(), INF);
    vector<int> distHeap(g.size(), INF); // Heap

	Heap* heap = criarHeap(30); // Heap
	Tupla vertice; // Heap

    fila.push({-0, source});
    inserirNoHeap(heap, -0, source, 0, 0); // Heap
    dist[source] = 0;
    distHeap[source] = 0;

    while (!fila.empty()) {
        int w = -fila.top().first;
        int u = fila.top().second;
        fila.pop();

	vertice = removeNoHeap(heap); // HEap
	int w1 = -vertice.d; // HEap
	int u1 = vertice.v; // HEap

	cout << "Conferir w e u: " << endl;
       	cout << "c++ " << " " << w << u << endl;
	cout << "c" << " " << w1 << u1 << endl;

        if (dist[u] < w) continue;

        for (const auto& [v, n_w] : g[u]) {
            if (dist[v] > w + n_w) {
                dist[v] = w + n_w;
		distHeap[v] = w1 + n_w; // Heap
                fila.push({-(w + n_w), v});
		inserirNoHeap(heap, -(w1 + n_w), v, 0, 0); // Heap 
            }
        }
    }

    cout << endl;
    comparaVetor(dist, distHeap);

    return dist;
}

void insereAresta(Grafo &g, int a, int b, int w) // a e b são vertices, w distancia
{
	a--; b--; // caso dele onde os vertices sao dados de 1 ate n
	g[a].push_back({b, w}); // insere ab
	g[b].push_back({a, w}); // insere ba
}

void imprimirGrafo(const Grafo &g) {
    for (int u = 0; u < g.size(); ++u) {
        cout << "Vértice " << u << ": "; // Adiciona 1 se os vértices são indexados a partir de 1
        for (const Aresta &aresta : g[u]) {
            cout << "(" << aresta.first << ", " << aresta.second << ") "; // Adiciona 1 para indexação a partir de 1
        }
        cout << endl;
    }
}

void solveAmb() // Funcao que resolve o problema das ambulancias
{
	Grafo grp = Grafo(n, vector<Aresta>());

	for(int i = 0; i < m; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		insereAresta(grp, a, b, w);
	}

	vector<int> hospitais(q);

	for(int &i : hospitais) cin >> i;

	vector<int> dist = dijkstra(grp, hospitais);

	int ans = -1;
	for(int x : dist) ans = max(ans, x);
	cout << ans << endl;
}

void solveIc()
{
	int N, M, X;
	cin >> N >> M >> X;
	Grafo grp = Grafo(N, vector<Aresta>());

	for(int i = 0; i < M; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		insereAresta(grp, a, b, w);
	}

	vector<int> friends(X);
	for(int &i : friends)
		cin >> i;

	
	vector<int> dist_to_friends = dijkstraOne(grp, 0);
	vector<int> dist_to_icecream = dijkstraOne(grp, N-1);
	
	int ans = INF;
	for(int fr : friends)
	{
		int w = dist_to_friends[fr-1] + dist_to_icecream[fr-1];
		ans = min(ans, w);
	}
	
	cout << endl;
	cout << ans << endl;
	
	imprimirGrafo(grp);
}

int main()
{_
	/*
	while(cin >> n >> m >> q)
	{
		solveAmb();
	}
	*/

	cout << "na main";
	solveIc();
}







