#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila* ultimo(Fila* fila){
    Fila* ultimo  = fila;
    for(ultimo; ultimo->prox!=NULL;ultimo=ultimo->prox){
        continue;
    }
    return ultimo;
}

Fila* adiciona_fila(Fila* fila, int pessoas){
    Fila* novo_no = (Fila*)malloc(sizeof(Fila));
    novo_no->prox=NULL;
    novo_no->pessoas=pessoas;
    if(fila==NULL){
        fila = novo_no;        
    }else{
        Fila* ultimo_no;
        ultimo_no = ultimo(fila);
        ultimo_no->prox=novo_no;
    }
    return fila;
}