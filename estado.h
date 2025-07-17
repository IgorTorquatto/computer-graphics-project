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

#endif
