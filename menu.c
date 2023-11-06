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
void retiraPratos(Mesas** restMesas,Pilha* pilhaPrato, int l, int c){
    int pratos_sobrando = 0;
    for(int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            if(restMesas[i][j].pessoas != restMesas[i][j].pratos && !restMesas[i][j].disponivel){
                pratos_sobrando = restMesas[i][j].pratos - restMesas[i][j].pessoas;
                restMesas[i][j].pratos = restMesas[i][j].pessoas;
                for(int k = 0; k < pratos_sobrando; k++){
                    pilha_push(pilhaPrato);
                }
            }
        }
    }
}
Fila* chegou_pessoas(Fila* fila, Mesas** restMesas, int l, int c, Pilha* pilhaPrato){
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
    }else{
        if(numPessoas>4){
            fila = adiciona_fila(fila,quatro);
            numPessoas = numPessoas-4;
            printf("Adicionando 4 pessoas na fila");
        }else{
            fila = adiciona_fila(fila,numPessoas);
            printf("Adicionando %d pessoas na fila", numPessoas);
            numPessoas=0;
        }
    }
}
    retiraPratos(restMesas, pilhaPrato, l, c);
    return fila;
}

int contaPratos(PratosLista* pilhaPratos){
    PratosLista* count;
    int c = 0;
    for(count = pilhaPratos; count!=NULL;count=count->prox){
        c++;
    }
    return c;
}

Mesas** aloca_rest(Mesas** restMesas, int l, int c, Pilha* pilhaPrato){
    int num = 1;
    int pratos = 0;
    restMesas = (Mesas**)malloc(l*sizeof(Mesas*));
    for(int i=0;i<l;i++){
        restMesas[i] = (Mesas*)malloc(c*sizeof(Mesas));
    }
    for(int j=0;j<l;j++){
        for(int k=0;k<c;k++){
            pratos = contaPratos(pilhaPrato->prim);
            restMesas[j][k].numMesa = num;
            restMesas[j][k].pessoas = 0;
            if(pratos>=4){
                restMesas[j][k].disponivel = true;
                restMesas[j][k].pratos = 4;
                for(int remove_prato = 0; remove_prato<4;remove_prato++){
                    pilha_pop(pilhaPrato);   
                }
            }else{
                restMesas[j][k].disponivel = false;
                restMesas[j][k].pratos = 0;
            }
            printf("%d ", restMesas[j][k].numMesa);
            num++;
        }
        printf("\n");
    }
    return restMesas;
}

void imprime_fila(Fila* fila){
    for(Fila* imprime=fila;imprime!=NULL;imprime=imprime->prox){
        printf(" Fila: %d | Ficha: %d \n", imprime->pessoas, imprime->ficha);
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
    printf("Qual mesa deseja arrumar? \n");
    scanf("%d",&qualMesa);
    for(int i=0;i<l;i++){
        for(int j=0;j<c;j++){
            if(restMesas[i][j].numMesa == qualMesa && restMesas[i][j].pratos == 0){
                if(numPratos>=4){
                    restMesas[i][j].pratos = 4;
                    restMesas[i][j].disponivel = true;
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
    printf("Deseja inserir quantos pratos? \n");
    scanf("%d", &p);
    for(int i=0;i<p;i++){
        pilha_push(pilhaPrato);
    }
}

Fila* finalizar_refeicao(Fila* fila, Mesas** restMesas, Pilha* pilhaPratos, int l, int c){
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
            }
        }
    }
    retiraPratos(restMesas, pilhaPratos, l, c);
    return fila;
}

Fila* desistirEspera(Fila* fila){
    int senha;
    printf("Qual a senha do grupo desistente? ");
    scanf("%d", &senha);
    fila = libera_senha(fila, senha);
    return fila;
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
    restMesas = aloca_rest(restMesas, l, c, pilhaPrato);
    while (aberto)
    {
        printf("1-Chegou Pessoas\n2-Finalizar Refeiçao\n3-Desistir da Fila\n4-Arruma Mesa \n5-Repor Pratos \n8-Printa Dados\n9-Sair\n");
        scanf("%d",&ctrl);
        switch (ctrl)
        {
        case 1:
            fila = chegou_pessoas(fila, restMesas, l, c, pilhaPrato);
            break;
        case 2:
            fila = finalizar_refeicao(fila,restMesas,pilhaPrato,l,c);
            break;
        case 3:
            fila = desistirEspera(fila);
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

/* A FAZER */
/*  ARRUMAR A FUNCAO DE FINALIZAR REFEICAO (BUG NA HORA DE TIRAR DA FILA E COLOCAR NA MESA) */
/* RELATORIOS */