#ifndef ESTADO_H
#define ESTADO_H

#include "estruturas.h"
#include "listaPontos.h"

typedef enum {
    MODO_NENHUM,
    MODO_PONTO,
    MODO_SELECAO
} ModoDesenho;

typedef enum {
    MENU_INICIAL,
    APLICACAO_EXECUTANDO
} EstadoApp;

extern ModoDesenho modoAtual;
extern EstadoApp estadoAtual;
extern ListaPontos listaPontos;

#endif
