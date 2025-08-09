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
int codigo(double x, double y, double xmin, double xmax, double ymin, double ymax);
int pickReta(double x0, double y0, double x1, double y1, double mx, double my, double t);
void selecionarRetaMaisProxima(ListaRetas* lista, double x, double y);
void deletarRetasSelecionadas(ListaRetas* lista);

#endif

