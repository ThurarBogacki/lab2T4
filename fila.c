#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila* ultimo(Fila* fila){
    Fila* last = fila;
    for(Fila* ultimo = fila; ultimo!=NULL;ultimo=ultimo->prox){
        last = ultimo;
    }
    return last;
}

Fila* adiciona_fila(Fila* fila, int pessoas){
    Fila* novo_no = (Fila*)malloc(sizeof(Fila));
    novo_no->prox=NULL;
    novo_no->pessoas=pessoas;
    if(fila==NULL){
        novo_no->ficha = 1;
        fila = novo_no;        
    }else{
        Fila* ultimo_no = (Fila*)malloc(sizeof(Fila));
        ultimo_no = ultimo(fila);
        novo_no->ficha = ultimo_no->ficha+1;
        ultimo_no->prox=novo_no;
    }
    return fila;
}

Fila* libera_senha(Fila* fila, int senha){
    Fila* atual = fila;
    Fila* anterior = fila;
    if(atual->ficha == senha){
        fila = atual->prox;
        return fila;
    }
    while (atual!=NULL)
    {
        if(atual==NULL){
            printf("Nao tem ninguem na fila\n");
        }else if(atual->ficha == senha){
            anterior->prox = atual->prox;
            free(atual);
            printf("achou");
            return fila;
        }
        Fila* aux;
        aux = atual;
        atual = atual->prox;
        anterior = aux;
        free(aux);
    }
    return fila;
}

Fila* removeFila(Fila* fila){
    if(fila==NULL){
        printf("Nao tem ninguem aguardando na fila");
        return fila;
    }else{
        Fila* head = fila->prox;
        free(fila);
        return head;
    }
}