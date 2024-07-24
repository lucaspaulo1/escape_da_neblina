import random
import itertools

def gerar_grafo(n):
    arestas = []
    todos_pares = list(itertools.combinations(range(n), 2))
    random.shuffle(todos_pares)

    for (u, v) in todos_pares:
        if len(arestas) >= n * (n - 1) // 2:
            break
        arestas.append((u, v, random.uniform(1.0, 10.0)))  # Peso aleatório entre 1.0 e 10.0

    return arestas

def salvar_grafo_em_arquivo(filename, grafos):
    with open(filename, 'w') as f:
        for (n, arestas) in grafos:
            f.write(f"{n} {len(arestas)}\n")
            for (u, v, peso) in arestas:
                f.write(f"{u} {v} {peso:.2f}\n")
            f.write("#END#\n")

def main():
    grafos = []
    for n in range(5, 201):  # De 5 a 200
        arestas = gerar_grafo(n)
        grafos.append((n, arestas))
    
    salvar_grafo_em_arquivo('grafos.txt', grafos)
    print("Grafos foram salvos em 'grafos.txt'.")

if __name__ == "__main__":
    main()

