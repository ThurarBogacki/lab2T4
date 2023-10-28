#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "fila.h"

Fila* chegou_pessoas(Fila* fila, Mesas** restMesas){
    int numPessoas;
    int quatro=4;
    printf("Quantas pessoas chegaram? ");
    scanf("%d",&numPessoas);
    while(numPessoas!=0){
        if(numPessoas>4){
            fila = adiciona_fila(fila,quatro);
            numPessoas-=4;
        }else{
            fila = adiciona_fila(fila,numPessoas);
            numPessoas=0;
        }
    }
    return fila;
}

Mesas** aloca_rest(Mesas** restMesas, int l, int c){
    int num = 1;
    restMesas = (Mesas**)malloc(l*sizeof(Mesas*));
    for(int i=0;i<l;i++){
        restMesas[i] = (Mesas*)malloc(c*sizeof(Mesas));
    }
    for(int j=0;j<l;j++){
        for(int k=0;k<c;k++){
            restMesas[j][k].numMesa = num;
            printf("%d ", restMesas[j][k].numMesa);
            num++;
        }
        printf("\n");
    }
    return restMesas;
}

void imprime_fila(Fila* fila){
    for(Fila* imprime=fila;imprime!=NULL;imprime=imprime->prox){
        printf("%d \n", imprime->pessoas);
    }
}

void open_rest(){
    Mesas** restMesas = NULL;
    Fila* fila = NULL;
    int ctrl, aberto=1;
    int l,c;
    printf("Qual a quantidade de linhas do restaurante? ");
    scanf("%d",&l);
    printf("Qual a quantidade de colunas do restaurante? ");
    scanf("%d",&c);
    restMesas = aloca_rest(restMesas, l, c);
    while (aberto)
    {
        printf("1-Menu\n2-Fila\n9-Sair");
        scanf("%d",&ctrl);
        switch (ctrl)
        {
        case 1:
            fila = chegou_pessoas(fila, restMesas);
            break;
        case 2:
            imprime_fila(fila);
            break;
        case 9:
            aberto=0;
            break;
        default:
            break;
        }
    }
    
}