#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

typedef struct palavra{
	char palavra[20];
	int valor, frequencia;
}Palavra;

typedef struct Hash {
	int qtd;
	struct palavra **itens;
}Hash;

//Cria a Hash (Vetor de struct que armazenara os dados).
Hash* criaHash();

//Apaga a hash.
void liberaHAsh (Hash *ha);

//Algoritmo para ordenar os dados (sele��o sort).
void SelectionSort(Palavra *pa,int n_elem);

//Trasformar string em valor.
int valorString (char* str);

//Insere dados na hash.
int insereHash_EnderAberto (Hash *ha, struct palavra pa);

//Procura um dado na hash.
int buscaHash_EnderAberto (Hash *ha, struct palavra *pa, int valor);

//Estr�tegia de endere�amento aberto, caso j� tenha elemento aloca no pr�ximo indice do vetor hash.
int sondagemLinear (int pos, int i);

//Fun��o de hash (m�todo da divis�o) para gerar chaves da hash.
int chaveDivisao (int chave);
