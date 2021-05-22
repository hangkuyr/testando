#ifndef TP1_H
#define TP1_H



/*
A lista de adjacência de um vértice v é composta por nós do tipo node. 
Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. 
Um link é um ponteiro para um node. 
*/

typedef struct jogador{
	int pos; //posição que o jogador jogou na ultima rodada
	int nome;
	int x, y;
	int valor;
}jogador;


typedef struct vertice{
	int x, y;
	int valor;
}vertice;

typedef struct node { 
   vertice *vert; 
   struct node *next; 
}node;


/* 
REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: 

A estrutura graph representa um grafo. 
O campo adj é um ponteiro para o vetor de listas de adjacência, 
o campo V contém o número de vértices 
e o campo A contém o número de arcos do grafo. 
*/

typedef struct grafo {
   int V; 
   int A; 
   node *adj; 
}grafo;

/* Um Graph é um ponteiro para um graph. */

typedef struct grafo *Grafo;

void insertionSort(jogador *arr, int n);

int rec(node *ptr, node *adj, int v, int n, int m, int **visited, int pos, vertice *q);

void jogo(int n, int m, node *adj, vertice **q, int **visited, jogador *jogadores, int k, int **tabuleiro);

node* criaMatriz(int n, int m, node *adj, int **tab);

vertice* novoV(int x, int y, int val);

node* novo( vertice *w, node *next);


#endif