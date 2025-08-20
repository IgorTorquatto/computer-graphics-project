#ifndef LISTAPONTOS_H
#define LISTAPONTOS_H

#include "estruturas.h"

typedef struct NoPonto {
    Ponto ponto;
    struct NoPonto* prox;
} NoPonto;

typedef struct {
    NoPonto* inicio;
    int contador;
} ListaPontos;

void criarListaPontos(ListaPontos* lista);
void inserirPonto(ListaPontos* lista, double x, double y);
void desenharPontos(ListaPontos* lista);
int pickPonto(float px, float py, float mx, float my, int t);
void selecionarPontoMaisProximo(ListaPontos* lista, int x, int y);
void deletarSelecionados(ListaPontos* lista);
Ponto* getPontoSelecionado(ListaPontos* lista);



#endif

