//Aluno: Renan Clarindo Amorim
//RA: 186454

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
	int indice;
	struct NODE *prox;
} NODE;

typedef struct GRAFO {
	char **palavra;
	struct NODE *liga;
	int tamanho;
} GRAFO;

typedef struct VISITA {
	int indice;
	int nivel;
} VISITA;


//checa se duas palavras diferem de uma letra
int diff (char a[], char b[]){
	int i;
	int count = 0;

	if (strlen(a) != strlen(b))
		return 0;

	int tam = strlen(a);
	for (i = 0; i<tam; i++){
		if (a[i] != b[i])
			count++;
		if (count > 1)
			break;
	}

	if (count == 1)
		return 1;
	else if (count == 0)
		return -1;
	else
		return 0;
}

//adiciona uma nova palavra no grafo, e já realiza as conexões necessárias (cada nó representa uma palavra e se liga a outras palavras que diferem por um letra)
void adicionar (GRAFO *g, char chave[]){
	int i;
	int d;
	NODE *temp = NULL;
	NODE *aux = NULL;

	strcpy(g->palavra[g->tamanho], chave);
	g->liga[g->tamanho].indice = -1;
	g->liga[g->tamanho].prox = NULL;
	temp = &(g->liga[g->tamanho]);
	
	for (i = 0; i < g->tamanho; i++){
		d = diff(g->palavra[i], chave);
		if (d == -1)
			return;

		if (d){
			aux = malloc(sizeof(NODE));
			aux->indice = i;
			aux->prox = NULL;

			temp->prox = aux;
			temp = temp->prox;

			aux = malloc(sizeof(NODE));
			aux->indice = g->tamanho;
			aux->prox = NULL;

			aux->prox = g->liga[i].prox;
			g->liga[i].prox = aux;
			
		}
	}

	g->tamanho += 1;
}

//Faz uma busca por largura, usando um laço pra simular uma fila
int distancia(GRAFO *g, int origem){
	
	int nivel = 0;

	int visitado[g->tamanho];
	for (int n = 0; n < g->tamanho; n++){
		visitado[n] = 0;
	}

	visitado[origem] = 1;

	// fila representada por um vetor
	VISITA visitar[g->tamanho];

	
	int k = 0;
	visitar[0].indice = origem;
	visitar[0].nivel = 0;
	k++;

	int i;
	int max = 0;
	NODE *aux = g->liga[origem].prox;

	//k representa o tamanho da fila
	for (i = 0; i < k; i++){
		aux = g->liga[visitar[i].indice].prox;
		nivel = visitar[i].nivel;
		if (max < nivel)
			max = nivel;
		// adiciona todos os filhos do nó atual a fila e incrementa o tamanho K
		while (aux != NULL){
			if (visitado[aux->indice] == 0){	
				visitar[k].indice = aux->indice;
				visitar[k].nivel = nivel+1;
				visitado[aux->indice] = 1;
				k++;
			}
			aux = aux->prox;
		}
	}

	return max;
}

// checa a maior distancia para todos os nós retornando a maior
int tamanho_grafo (GRAFO *g){
	int i;
	int temp;
	int	maior = 0;

	for (i = 0; i < g->tamanho; i++){
		

		temp = distancia (g, i);


		if (temp != 20001 && temp > maior)
			maior = temp;
	}

	return (maior);
}

//libera memoria
void liberar (GRAFO *g){
	int i;
	
	NODE *aux = NULL;
	NODE *aux2 = NULL;
	for (i = 0; i< g->tamanho; i++ ){
		
		for (aux = g->liga[i].prox; aux != NULL; free(aux2)){
			aux2 = aux;
			aux = aux->prox;
		}
	}

	for (i = 0; i< 20000; i++ ){
		free (g->palavra[i]);
	}


	free (g->liga);
	free (g->palavra);
}

int main (){
	char input[30];
	int i;

	GRAFO *grafo = malloc (sizeof(GRAFO));
	grafo->tamanho = 0;
	grafo->liga = calloc(20000, sizeof(NODE));
	grafo->palavra = calloc (20000, sizeof(char*));
	for (i = 0; i < 20000; i++)
		grafo->palavra[i] = malloc(30 * sizeof(char));

	while(scanf("%s", input) != EOF){
		adicionar (grafo, input);
	}

	printf ("%d\n",tamanho_grafo(grafo));

	liberar(grafo);
	free(grafo);

	return 0;
} 