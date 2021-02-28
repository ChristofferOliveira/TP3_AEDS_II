#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Hashing.c"
#define pause getch();

int main(int argc, char **argv){
    FILE *a1, *a2;
    int i,j = 0,x,ctdprint = 0;
    char lida[20];
    a1 = fopen(argv[1] , "r");
    Hash *ha = criaHash();
    while(!feof(a1)){//lendo e deixando a palavra padrão
        fscanf(a1,"%s",lida);
        for(i = 0; lida[i] != '\0'; i++){
            if((lida[i] >= 65 && lida[i] <= 90) || (lida[i] >= 97 && lida[i] <= 122) || (lida[i] == 45) ){//olhan se é uma letra ou - para palavras como pe-de-moleque
                if(lida[i] >= 65 && lida[i] <= 90){//passando a letra para minuscula caso ela esteja maiuscula.
                    lida[i] = lida[i] + 32;
                }
            }
            else{//colocando \0 no final caso não seja uma letra o caracter final da palavra
                lida[i] = '\0';
                i--;
            }
        }
        Palavra nova;
        strcpy(nova.palavra,lida);
        nova.frequencia = 1;
        nova.valor = 0;
        x = insereHash_EnderAberto(ha,nova);
    }
    for(i = 0; i < MAX - 1; i++){ // Contando quantas paavras são buscadas
        if(ha ->itens[i] != NULL ){
            if((ha ->itens[i] -> frequencia >= 2) && (strlen(ha->itens[i]->palavra) > 1)){
                ctdprint ++;
            }
        }
    }
    Palavra *armazena;
    armazena = (Palavra *) malloc(ctdprint * sizeof(struct palavra));
    for(i = 0; i < MAX - 1; i++){ //Colocando as palavras buscadas em outro vetor
        if(ha ->itens[i] != NULL ){
            if((ha ->itens[i] -> frequencia >= 2) && (strlen(ha->itens[i]->palavra) > 1)){
                armazena[j] = *(ha->itens[i]);
                j++;
            }
        }
    }
    SelectionSort(armazena,ctdprint); //Ordenando o novo vetor em ordem decrescente de frequecia e ordem lexicográfica para palavras iguais.
    for(i = 0; i < ctdprint; i++){
        printf("%d %s\n",armazena[i].frequencia,armazena[i].palavra);
    }
    fclose(a1);
    return 0;

}
