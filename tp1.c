#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"

/*
Criar função que decide proximo jogador
Criar função que cria matriz de adjascencia -> Construir matriz real,
	descobrir para quais posições bidimensionais cada vertice alcança
Rodar bfs
Utilizando cada jogada na sequencia do jogo
Definir vencedor

*/


//para o primeiro elemento da lista o next é null
node* novo( vertice *w, node *next) {
   node *a = malloc( sizeof (struct node));
   a->vert = w;
   a->next = next;
   return a;
}

vertice* novoV(int x, int y, int val){
	vertice *vert = (vertice *) malloc(sizeof(vertice));
	vert->x = x;
	vert->y = y;
	vert->valor = val;

	return vert;
}

//ordena os jogadores pelo que andou menos na ultima rodada e no empate a ordem de quem jogou
void insertionSort(jogador *arr, int n){
    int i, j;
    jogador *key = (jogador*) malloc(sizeof(jogador));
    for (i = 1; i < n; i++) {
        key->nome = arr[i].nome;
        key->valor = arr[i].valor;
        key->pos = arr[i].pos;
        key->x = arr[i].x;
        key->y = arr[i].y;
        j = i - 1;
        while (j >= 0 && arr[j].valor >= key->valor) {
            arr[j + 1].x = arr[j].x;
            arr[j + 1].y = arr[j].y;
            arr[j + 1].valor = arr[j].valor;
            arr[j + 1].pos = arr[j].pos;
            arr[j + 1].nome = arr[j].nome;
            j = j - 1;
        }
        arr[j + 1].nome = key->nome;
        arr[j + 1].valor = key->valor;
        arr[j + 1].pos = key->pos;
        arr[j + 1].x = key->x;
        arr[j + 1].y = key->y;
    }
    free(key);
}

int rec(node *ptr, node *adj, int v, int n, int m, int **visited, int pos, vertice *q){

	if(ptr == NULL){ //elemento nao tem mais para onde ir
		return 0;
	}
	else if(ptr->vert->x == n-1 && ptr->vert->y == m-1){ //elemento chegou na ultima posição do tabuleiro
		visited[ptr->vert->x][ptr->vert->y] = 1;
		q[pos].x = ptr->vert->x;
		q[pos].y = ptr->vert->y;
		pos++;
		return pos;
	}else if(visited[ptr->vert->x][ptr->vert->y] == 0){
		visited[ptr->vert->x][ptr->vert->y] = 1;
		q[pos].x = ptr->vert->x;
		q[pos].y = ptr->vert->y;
		pos++;
		int ret = 0;
		node* aux = adj[(m*ptr->vert->x)+ptr->vert->y].next;
		while(aux != NULL && ret == 0){
			ret = rec(aux, adj, v, n, m, visited, pos, q); //elemento faz chamada recursiva para o proximo passo
			aux = aux->next;
		}
		if(ret > 0){
			return ret;
		}else{
			visited[ptr->vert->x][ptr->vert->y] = 0;
			pos--;
			return rec(ptr->next, adj, v, n, m, visited, pos, q); //elemento tenta outra direção
		}
	}else{ //elemento ta em loop no tabuleiro
		return 0;
	}
}

void jogo(int n, int m, node *adj, vertice **q, int **visited, jogador *jogadores, int k, int **tabuleiro) {
	node *ptr;

	int v, i;
	int semWinner = 1;

	int jogadas = 0;
	int *result = (int *) malloc(sizeof(int) * k);
	for(i = 0; i < k; i++){
		result[i] = 0;
		v = jogadores[i].x*m+jogadores[i].y;
		ptr = adj[v].next;
		while(ptr != NULL && result[i] == 0){
			result[i] = rec(ptr, adj, v, n, m, visited, jogadas, q[i]); //chama a recursão para cada jogador, para encontrar o caminho percorrido para a vitoria
			ptr = ptr->next;
		}
		if(result[i])
			semWinner = 0;
	}

	jogadas = 0;
	int fimJogo = 1;
	if(semWinner){
		printf("SEM VENCEDORES\n");
	}else
		while(fimJogo){
			for(i = 0; i < k; i++){
				if(q[i][jogadas].x == n-1 && q[i][jogadas].y == m-1){
					printf("%c\n", jogadores[i].nome);
					printf("%d\n", ++jogadas);
					i = k;
					fimJogo = 0;
				}
			}
			insertionSort(jogadores, k);
			for(i = 0; i < k; i++){
				jogadores[i].x = q[jogadores[i].pos][jogadas].x;
				jogadores[i].y = q[jogadores[i].pos][jogadas].y;
				jogadores[i].valor = tabuleiro[q[jogadores[i].pos][jogadas].x][q[jogadores[i].pos][jogadas].y];
			}
			jogadas++;
		}

	free(result);
}

node* criaMatriz(int n, int m, node *adj, int **tab){
	int pos = 0, i, j;
	for(i = 0; i < n; i++){ //linha
		for(j = 0; j < m; j++){ //coluna
			if(i-tab[i][j] >= 0){ //jogador pode ir para cima
				//cria um node
				vertice *vert = novoV(i-tab[i][j], j, tab[i-tab[i][j]][j]);
				node *no = novo(vert, adj[pos].next);
				adj[pos].next = no;
			}
			if(i+tab[i][j] < n){ //jogador pode ir para baixo
				vertice *vert = novoV(i+tab[i][j], j, tab[i+tab[i][j]][j]);
				node *no = novo(vert, adj[pos].next);
				adj[pos].next = no;
			}
			if(j-tab[i][j] >= 0){ //jogador pode ir para  a esquerda
				vertice *vert = novoV(i, j-tab[i][j], tab[i][j-tab[i][j]]);
				node *no = novo(vert, adj[pos].next);
				adj[pos].next = no;
			}
			if(j+tab[i][j] < m){ //jogador pode ir para a direita
				vertice *vert = novoV(i, j+tab[i][j], tab[i][j+tab[i][j]]);
				node *no = novo(vert, adj[pos].next);
				adj[pos].next = no;
			}
			pos++;

		}
	}


	return adj;
}
