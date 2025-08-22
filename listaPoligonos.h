#ifndef LISTA_POLIGONOS_H
#define LISTA_POLIGONOS_H

#include "estruturas.h"

typedef struct noPoligono {
    Poligono poligono;
    struct noPoligono* prox;
} NoPoligono;

typedef struct {
    NoPoligono* inicio;
    int tamanho;
} ListaPoligonos;

void criarListaPoligonos(ListaPoligonos* lista);
void inserirPoligonoFim(ListaPoligonos* lista, Poligono p);
void desenharPoligonos(ListaPoligonos* lista);
void ListaPoligonosInserirFim(ListaPoligonos* lista, Poligono p);
//void selecionarPoligonoMaisProximo(ListaPoligonos* lista, int x, int y);
void selecionarPoli(ListaPoligonos* lista, int x, int y);
void deletarPoligonosSelecionados(ListaPoligonos* lista);

#endif

