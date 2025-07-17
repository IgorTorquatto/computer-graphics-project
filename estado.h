#ifndef ESTADO_H
#define ESTADO_H

#include "estruturas.h"
#include "listaPontos.h"
#include "listaRetas.h"

typedef enum {
    MODO_NENHUM,
    MODO_PONTO,
    MODO_SELECAO,
    MODO_RETA
} ModoDesenho;

typedef enum {
    MENU_INICIAL,
    APLICACAO_EXECUTANDO
} EstadoApp;

extern ModoDesenho modoAtual;
extern EstadoApp estadoAtual;
extern ListaPontos listaPontos;
extern ListaRetas listaRetas;

//Para criar pré-visualização no segmento de reta
extern int criandoReta;
extern double retaTempX1, retaTempY1;
extern double retaTempX2, retaTempY2;


#endif
