CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

# Lista de arquivos-fonte (todos os .c no diretório src)
SRCS = $(wildcard $(SRC)/*.c)

# Gere a lista de objetos a partir dos arquivos-fonte
OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

EXE = $(BIN)/tp2.out

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

# Regra para compilar cada arquivo-fonte
$(OBJ)/%.o: $(SRC)/%.c $(wildcard $(INC)/*.h)
	$(CC) -g $(CFLAGS) -o $@ -c $<

# Limpeza
clean:
	rm -f $(EXE) $(OBJS) gmon.out

# Regra para executar o programa
run: $(EXE)
	./$(EXE) < inputs.txt

# Regra para executar o Valgrind
valgrind: $(EXE)
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) < inputs.txt

# teste
gen: 
	@c++ -g ./src/no.c ./src/lista_encadeada.c ./src/graph.c ./src/grafo_matriz_adjacencia.c ./src/fila_prioridade.c ./src/encontrar_caminho.c eique.c -o asdas
	@./asdas
	
