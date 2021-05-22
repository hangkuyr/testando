#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"
#include <sys/time.h>

int main(int argc, char *argv[]) {


	struct timeval inicio, final;
	int tmili;
	gettimeofday(&inicio, NULL);


	FILE *arq = fopen(argv[1], "r");

	int n, m, k, i, j;
	fscanf(arq, "%d", &n);
	fscanf(arq, "%d", &m);


	fscanf(arq, "%d", &k);
	//criando mapa que será usado para traçar o caminho percorrido por cada jogador
	vertice **q = (vertice **) malloc(sizeof(vertice*) * k);
	for(i = 0; i < k; i++){
		q[i] = (vertice *) malloc(sizeof(vertice) * n*m);
	}

	//Criando tabuleiro do jogo e mapa de visitados
	int **visited = (int **) malloc(sizeof(int*) * n);
	int **tabuleiro = (int **) malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++){

		tabuleiro[i] = (int *) malloc(sizeof(int) * m);
		visited[i] = (int *) malloc(sizeof(int) * m);
	}
	//A estruturas de dados q guarda os caminhos percorridos pelo tabuleiro para os jogadores
	int ii;
	for(ii = 0; ii< k; ii++){
		int aux = 0;
		for(i=0; i < n; i++) {
			for(j=0;j<m;j++) {
				q[ii][aux].x = 0;
				q[ii][aux].y = 0;
				q[ii][aux].valor = 0;

			}
		}
	}

	for(i=0; i<n; i++) {
		for(j=0;j<m;j++) {
			visited[i][j] = 0;
			fscanf(arq, "%d", &tabuleiro[i][j]);
		}
	}

	jogador *jogadores = (jogador *) malloc(sizeof(jogador) * k);
	int nome = 65; //Começa com o valor ascII do caracter 'A'
	for(i=0; i < k; i++){
		int x1, y1;
		fscanf(arq, "%d %d", &x1, &y1);
		jogadores[i].x = x1;
		jogadores[i].y = y1;
		jogadores[i].valor = tabuleiro[jogadores[i].x][jogadores[i].y];
		jogadores[i].nome = nome;
		jogadores[i].pos = i;
		nome++;
	}

	//Criando o vetor de adjacencia
	node *adj = (node *) malloc(sizeof(node) * n*m);
	int qtd = 0;
	for(i=0; i<n; i++) {
		for(j=0;j<m;j++) {
			vertice *vet = (vertice *) malloc(sizeof(vertice));
			vet->x = i;
			vet->y = j;
			vet->valor = tabuleiro[i][j];
			adj[qtd].vert = vet;
			adj[qtd].next = NULL;
			qtd++;
		}
	}

	grafo *G = (grafo*) malloc(sizeof(grafo));
	G->V = n*m;
	G->A = 0;
   	G->adj = criaMatriz(n, m, adj, tabuleiro);


   	//começa as rodadas de jogadas decididas pelas regras de proxima vez do jogo

	jogo(n, m, adj, q, visited, jogadores, k, tabuleiro);

	//Liberação de toda memória alocada pelo programa

	for(i = 0; i < k; i++){
		free(q[i]);
	}
	free(jogadores);
	free(q);
	qtd = 0;
	for(i=0; i < n; i++) {
		free(tabuleiro[i]);
		free(visited[i]);
		for(j=0;j<m;j++) {
			free(adj[qtd].vert);
			node *ptr = adj[qtd].next;
			while(ptr != NULL){
				node *aux = ptr->next;
				free(ptr->vert);
				free(ptr);
				ptr = aux;
			}
			qtd++;
		}
	}
	free(adj);
	free(tabuleiro);
	free(visited);
	free(G);

	fclose(arq);

	gettimeofday(&final, NULL);
  	tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

  	// printf("tempo decorrido: %d\n", tmili);


	return 0;
}
