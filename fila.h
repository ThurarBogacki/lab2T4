struct fila{
    int pessoas;
    struct fila* prox;
}; typedef struct fila Fila;

Fila* adiciona_fila(Fila* fila, int pessoas);