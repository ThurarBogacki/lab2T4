struct fila{
    int pessoas;
    int ficha;
    struct fila* prox;
}; typedef struct fila Fila;

Fila* adiciona_fila(Fila* fila, int pessoas);
Fila* libera_senha(Fila* fila, int senha);
Fila* removeFila(Fila* fila);