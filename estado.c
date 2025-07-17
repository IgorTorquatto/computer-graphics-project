#include "estado.h"

ModoDesenho modoAtual = MODO_NENHUM;
EstadoApp estadoAtual = MENU_INICIAL;

ListaPontos listaPontos;
ListaRetas listaRetas;

void inicializarEstados() {
    criarListaPontos(&listaPontos);
    criarListaRetas(&listaRetas);
}

