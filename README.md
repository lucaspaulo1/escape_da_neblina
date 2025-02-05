# Introdução
Este trabalho prático aborda a implementação e análise experimental de algoritmos
para resolver um problema de caminhos mínimos em grafos. O cenário é uma floresta fictícia
onde o herói Linque precisa escapar antes que sua energia se esgote. A floresta é composta por
$$n$$ clareiras conectadas por trilhas unidirecionais. Algumas clareiras possuem portais
mágicos que permitem a viagem instantânea sem consumo de energia.
Linque começa na clareira 0 e deve chegar à clareira $$n-1$$, consumindo no máximo uma
quantidade $$m$$ limitada de energia, s, e utilizando os portais no máximo $$k$$ vezes.
Para determinar se Linque pode escapar da floresta, utilizaremos o algoritmo de Dijkstra
e o algoritmo (A-estrela). Ambos são algoritmos clássicos para encontrar
caminhos mínimos em grafos, sendo o uma extensão do com uso de heurística
para guiar a busca.
Este trabalho se concentra nos aspectos de implementação desses algoritmos e na
análise experimental dos resultados obtidos.

O problema foi modelado usando grafos, e resolvido usando algoritmos de caminhamento mínimo.

# Estrutura do projeto
```
├── include/
│   ├── encontrar_caminho.h
│   ├── fila_prioridade.h
│   ├── grafo_matriz_adjacencia.h
│   ├── graph.h
│   ├── lista_encadeada.h
│   ├── no.h
│   ├── ponto.h
├── src/
│   ├── encontrar_caminho.cpp
│   ├── fila_prioridade.cpp
│   ├── grafo_matriz_adjacencia.cpp
│   ├── graph.cpp
│   ├── lista_encadeada.cpp
│   ├── main.cpp
│   ├── no.cpp
│   ├── ponto.cpp
├── obj/
├── bin/
├── Makefile 
```
Obs1: As pastas bin e obj permanecem vazias até que o programa seja compilado.
Obs2: O arquivo `inputs.txt` é apenas um exemplo de entrada válida para o problema.

# Entradas e Saídas
As entradas do programa são feitas via linha de comando.
## Exemplo
Considere a entrada do exemplo a seguir:
```
5 4 2
0 1
0 0
0 2
1 1
10 2
0 1
0 3
1 4
2 4
0 2
3 4
1 1
```
As instâncias serão lidas pela entrada padrão. A primeira linha consiste em três inteiros
n, m e k que representam, respectivamente, quantos vértices, trilhas e portais a floresta
possui. As próximas n linhas possuem dois números racionais x e y, descrevendo as coorde-
nadas de cada clareira em um plano. A seguir, as próximas m linhas possuem dois inteiros
u e v, indicando que existe uma trilha entre as duas clareiras, que só pode ser percorrida
começando em u e terminando em v. Por fim, as próximas k linhas possuem também dois
inteiros u e v, indicando quais clareiras são conectadas por portais (os portais também só
podem ser atravessados começando em u e terminando em v). A última linha
contém um número racional s indicando a quantidade de energia que Linque possui para
caminhar e um inteiro q indicando quantos portais podem ser utilizados.

Para essa entrada temos a saı́da:
```
185
5
105
2
1 6 30
5 6 15
```
A saída da execução de um algoritmo serão dois inteiros. O primeiro, utilizando o al-
goritmo Djikstra imprime 1 caso exista caminho de custo no máximo s e que cruze no
máximo q portais e 0 caso contrário. De forma análoga, o mesmo para o algoritmo
A*.

# Uso
Dentro do projeto, execute os seguintes comandos para compilar o projeto:
```
make clean
```
```
make all
```

O programa será lido pela entrada padrão através de linha de comando, como por exemplo:
```
./bin/tp2.out < inputs.txt
```
Ou, semelhantemente, com o comando:
```
make run
```
Onde `inputs.txt` é um arquivo com uma entrada válida dentro.
Obs: Para o `make run` funcionar é necessáio o arquivo inputs.txt
