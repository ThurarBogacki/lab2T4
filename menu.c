#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "fila.h"
#include "pilha.h"

bool tem_mesa(Mesas** restMesas, int l, int c){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            if(restMesas[i][j].disponivel){
                return true;
            }
        }
    }
    return false;
}

Fila* chegou_pessoas(Fila* fila, Mesas** restMesas, int l, int c){
    int numPessoas;
    int quatro=4;
    printf("Quantas pessoas chegaram? ");
    scanf("%d",&numPessoas);
    while(numPessoas!=0){
        if(tem_mesa(restMesas, l, c)){
            if(numPessoas>4){
                for(int i=0;i<l;i++){
                    for(int j=0;j<c;j++){
                        if(restMesas[i][j].disponivel){
                            restMesas[i][j].disponivel = false;
                            restMesas[i][j].pessoas = 4;
                            numPessoas= numPessoas-4;
                            i = l+1; // NUMERO MAGICO PRA SAIR DO LOOP
                            j = c+1; // NUMERO MAGICO PRA SAIR DO LOOP
                        }
                    }
                }
            }else{
                for(int k=0;k<l;k++){
                    for(int l=0;l<c;l++){
                        if(restMesas[k][l].disponivel){
                            restMesas[k][l].disponivel = false;
                            restMesas[k][l].pessoas = numPessoas;
                            numPessoas = 0;
                            k = l+1; // NUMERO MAGICO PRA SAIR DO LOOP
                            l = c+1; // NUMERO MAGICO PRA SAIR DO LOOP                        }
                    }
                }
            }
        }
    }else if(!tem_mesa(restMesas, l, c)){
        if(numPessoas>4){
            fila = adiciona_fila(fila,quatro);
            numPessoas = numPessoas-4;
        }else{
            fila = adiciona_fila(fila,numPessoas);
            numPessoas=0;
        }
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
            restMesas[j][k].disponivel = true;
            restMesas[j][k].pessoas = 0;
            restMesas[j][k].pratos = 0;
            printf("%d ", restMesas[j][k].numMesa);
            num++;
        }
        printf("\n");
    }
    return restMesas;
}

void imprime_fila(Fila* fila){
    for(Fila* imprime=fila;imprime!=NULL;imprime=imprime->prox){
        printf(" Fila: %d \n", imprime->pessoas);
    }
}


void imprimeMesa(Mesas** restMesas, int l, int c){
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            printf("Nmro Mesa: %d / Pessoas: %d / Pratos: %d /",restMesas[i][j].numMesa, restMesas[i][j].pessoas, restMesas[i][j].pratos);
            printf("Disponibilidade: %d  |  ", restMesas[i][j].disponivel);
            printf("\n");
        }
    printf("\n");
    printf("\n");
    }
}

int quantidadePratos(Pilha* pilhaPrato){
    int count=0;
    for(PratosLista* p=pilhaPrato->prim;p!=NULL;p=p->prox){
        count++;
    }
    return count;
}

void arrumaMesas(Pilha* pilhaPrato, Mesas** restMesas, int l, int c){
    int numPratos;
    int qualMesa;
    numPratos = quantidadePratos(pilhaPrato);
    printf("Qual mesa deseja arrumar? ");
    scanf("%d",&qualMesa);
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            if(restMesas[i][j].numMesa == qualMesa && restMesas[i][j].disponivel && restMesas[i][j].pratos !=4){
                if(numPratos>=4){
                    restMesas[i][j].pratos = 4;
                    for(int pop=0;pop<4;pop++){
                        pilha_pop(pilhaPrato);
                    }
                }else{
                    printf("Pratos insuficientes\n");
                }
            }
        }
    }
}

void imprime_pilha(Pilha* pilhaPrato){
    int count=0;
    for(PratosLista* imprime=pilhaPrato->prim;imprime!=NULL;imprime=imprime->prox){
        count++;
    }
    printf("Pratos na Pilha: %d \n", count);
}

void insere_pilha(Pilha* pilhaPrato){
    int p;
    printf("Deseja inserir quantos pratos? ");
    scanf("%d", &p);
    for(int i=0;i<p;i++){
        pilha_push(pilhaPrato);
    }
}

Fila* verifica_fila(Mesas** restMesas, Fila* fila, int qualMesa, int l, int c){
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            if(restMesas[i][j].numMesa == qualMesa && restMesas[i][j].disponivel){
                if(fila!=NULL){
                    restMesas[i][j].disponivel = false;
                    restMesas[i][j].pessoas = fila->pessoas;
                    Fila* t = fila;
                    fila = fila->prox;
                    free(t);
                }
            }
        }
    }
    return fila;
}

void finalizar_refeicao(Fila* fila, Mesas** restMesas, Pilha* pilhaPratos, int l, int c){
    int qualMesa, numPratos;
    numPratos = quantidadePratos(pilhaPratos);
    printf("Qual mesa deseja finalizar a refeicao? ");
    scanf("%d",&qualMesa);
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            if(restMesas[i][j].numMesa == qualMesa && restMesas[i][j].disponivel == false){
                restMesas[i][j].disponivel = true;
                restMesas[i][j].pessoas = 0;
                restMesas[i][j].pratos = 0;
                if(numPratos>=4){
                    restMesas[i][j].pratos = 4;
                    for(int pop=0;pop<4;pop++){
                        pilha_pop(pilhaPratos);
                    }
                }else{
                    printf("Pratos insuficientes\n");
                }
                fila = verifica_fila(restMesas, fila, qualMesa, l, c);
            }
        }
    }
}

void open_rest(){
    Mesas** restMesas = NULL;
    Pilha* pilhaPrato = pilha_cria();
    Fila* fila = NULL;
    int ctrl, aberto=1;
    int l,c,p;
    printf("Qual a quantidade de linhas do restaurante? ");
    scanf("%d",&l);
    printf("Qual a quantidade de colunas do restaurante? ");
    scanf("%d",&c);
    printf("Deseja iniciar o restaurante com quantos pratos? ");
    scanf("%d", &p);
    for(int i=0;i<p;i++){
        pilha_push(pilhaPrato);
    }
    restMesas = aloca_rest(restMesas, l, c);
    while (aberto)
    {
        printf("1-Chegou Pessoas\n4-Arruma Mesa \n5-Insere Pilha Prato \n8-Printa Dados\n9-Sair\n");
        scanf("%d",&ctrl);
        switch (ctrl)
        {
        case 1:
            fila = chegou_pessoas(fila, restMesas, l, c);
            break;
        case 2:
            finalizar_refeicao(fila,restMesas,pilhaPrato,l,c);
            break;
        case 4:
            arrumaMesas(pilhaPrato,restMesas,l,c);
            break;
        case 5:
            insere_pilha(pilhaPrato);
            break;
        case 8:
            imprimeMesa(restMesas, l, c);
            imprime_fila(fila);
            imprime_pilha(pilhaPrato);
            break;
        case 9:
            aberto=0;
            break;
        default:
            break;
        }
    }
    
}