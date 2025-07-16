#ifndef LISTAPONTOS_H
#define LISTAPONTOS_H

#include "estruturas.h"

typedef struct NoPonto {
    Ponto ponto;
    struct NoPonto* prox;
} NoPonto;

typedef struct {
    NoPonto* inicio;
    int contador; // para gerar ids
} ListaPontos;

void criarListaPontos(ListaPontos* lista);
void inserirPonto(ListaPontos* lista, double x, double y);
void desenharPontos(ListaPontos* lista);

#endif

