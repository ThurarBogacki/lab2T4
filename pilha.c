#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

Pilha* pilha_cria (void)
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}

void pilha_push (Pilha* p)
{
    PratosLista* n = (PratosLista*) malloc(sizeof(PratosLista));
    n->v = 1;
    n->prox = p->prim;
    p->prim = n;
}

int pilha_vazia(Pilha* p){
    return(p->prim==NULL);
}

void pilha_pop (Pilha* p)
{
    PratosLista* t;
    if (pilha_vazia(p))
    {
        printf("*** Acabou os pratos (adicione mais pratos a pilha)\n");
        return;
    }
    t = p->prim;
    p->prim = t->prox;
    free(t);
}