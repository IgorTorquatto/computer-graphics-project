#ifndef LISTA_RETAS_H
#define LISTA_RETAS_H

#include "estruturas.h"

typedef struct noReta {
    Reta reta;
    struct noReta* prox;
} NoReta;

typedef struct {
    NoReta* inicio;
    int tamanho;
} ListaRetas;

void criarListaRetas(ListaRetas* lista);
void ListaRetasInserirFim(ListaRetas* lista, Reta r);
void desenharRetas(ListaRetas* lista);
void selecionarRetaMaisProxima(ListaRetas* lista, double x, double y);
void deletarRetasSelecionadas(ListaRetas* lista);

#endif

