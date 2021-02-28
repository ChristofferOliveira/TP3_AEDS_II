#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Hashing.h"
#define MAX 256
#define pause getch();

Hash* criaHash(){
	Hash* ha = (Hash*) malloc (sizeof(Hash));
	if(ha != NULL){ //se a alocação foi feita com sucesso.
		int i;
		ha -> itens = (struct palavra**) malloc (MAX * sizeof(struct palavra *));
		if (ha -> itens == NULL){//Alocação com erro.
			free(ha);
			return NULL;
		}
		ha -> qtd = 0;
		for(i = 0; i < MAX-1; i++){//inicializando todos os espaços do hash com NULL
			ha -> itens[i] = NULL;
		}
		return ha;
	}
}

void liberaHAsh (Hash *ha){
	if(ha != NULL){
		int i;
		for(i = 0; i < MAX - 1; i++){
			if(ha -> itens[i] != NULL)
				free(ha -> itens[i]);
			free(ha -> itens);
			free(ha);
		}
	}
}

void SelectionSort(Palavra *pa,int n_elem){
    int i,j,maior;
    Palavra troca;
    for(i = 0; i < n_elem-1; i++){
        maior = i;

        //Procurando o menor elemnto em relação a'i'.

        for(j = i+1; j < n_elem; j++){
            if(pa[j].frequencia >= pa[maior].frequencia){
                if(pa[j].frequencia == pa[maior].frequencia){
                    if(strcmp(pa[j].palavra,pa[maior].palavra) < 0){
                        troca = pa[j];
                        pa[j] = pa[maior];
                        pa[maior] = troca;
                    }
                }
                else{
                    maior = j;
                }

            }
        }
        //Troca os valores de posição atual com a 'menor'.

        if(i != maior){
            troca = pa[i];
            pa[i] = pa[maior];
            pa[maior] = troca;
        }
    }
}

int valorString (char* str){//Transformando a string em um valor para se calcular a posição.
	int i,valor = 7;
	int tam = strlen (str);
	for(i = 0; i < tam; i++){
		valor = 31 * valor + (int)str[i]; //Calculando o valor para a string.
	}
	return valor;
}

int chaveDivisao (int chave){ //Calculado a posição que ficará na hash.
	return (chave & 0x7FFFFFFF) % MAX;
}

int sondagemLinear (int pos,int i){//Resto da divição pelo tamanho da Hash
	return ((pos + i) & 0x7FFFFFFF) % MAX;//Fazendo o 'e' bit a bit para evitar overflow em seguida pegando o resto da divisão.
}

int insereHash_EnderAberto(Hash* ha , struct palavra pa){
	if(ha == NULL || ha -> qtd == MAX) //Hash cheia ou n criada.
		return 0;
	int chave = valorString (pa.palavra);
	if(strlen(pa.palavra) <= 1){//Apenas palavras com mais de 1 caracter.
        return 1;
	}
	int i, pos, novaPos;
	pa.valor = chave;
	pos = chaveDivisao (chave);

	/*Caso tenha algum elemento no lugar calculado, não faz nenhuma inserção e tenta colocar na posição
	seguinte da calculada e assim  por diante até que encontre NULL ou veririficar toda hash.*/

	for(i = 0; i < MAX - 1; i++){
		novaPos = sondagemLinear (pos, i);
        if(ha -> itens[novaPos] != NULL){
            if(strcmp(ha ->itens[novaPos]->palavra,pa.palavra) == 0){
                ha ->itens[novaPos] -> frequencia = ha ->itens[novaPos] -> frequencia + 1;
                return 1;
            }
        }
        else{
            if(ha -> itens[novaPos] == NULL){
                struct palavra* nova;
                nova = (struct palavra *) malloc (sizeof(struct palavra));
                if(nova == NULL) //Probelema na alocação.
                    return 0;
                *nova = pa;
                ha -> itens[novaPos] = nova;
                ha -> qtd++;
                return 1;
            }
		}
	}
	return 0;
}

int buscaHash_EnderAberto (Hash *ha, struct palavra *pa, int vlr){
	if (ha == NULL)
		return 0;
	int i, pos, novaPos;
	pos = chaveDivisao (pa -> valor);
	for(i = 0; i < MAX -1; i++){
		novaPos = sondagemLinear (pos,i);
		if(ha -> itens[novaPos] == NULL)
			return 0;
		if(ha -> itens[novaPos] -> valor == vlr){//Buscando pelo valor da pesquisa
			*pa = *(ha -> itens[novaPos]);//struct desejada recebe a struct que contem o valor buscado.
			return 1;
		}
	}
	return 0;
}
