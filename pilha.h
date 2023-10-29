struct pratosLista
{
    int v;
    struct pratosLista* prox;
};typedef struct pratosLista PratosLista;

struct pilha{
    struct pratosLista* prim;
};typedef struct pilha Pilha;

Pilha* pilha_cria (void);
void pilha_push (Pilha* p);
void pilha_pop (Pilha* p);
int pilha_vazia(Pilha* p);