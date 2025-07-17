#include "estado.h"

ModoDesenho modoAtual = MODO_NENHUM;
EstadoApp estadoAtual = MENU_INICIAL;

ListaPontos listaPontos;
ListaRetas listaRetas;

// Para criar pr�-visualiza��o do segmento de reta
int criandoReta = 0;
double retaTempX1, retaTempY1;
double retaTempX2, retaTempY2;


void inicializarEstados() {
    criarListaPontos(&listaPontos);
    criarListaRetas(&listaRetas);
}

