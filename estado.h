#ifndef ESTADO_H
#define ESTADO_H

#include "estruturas.h"
#include "listaPontos.h"
#include "listaRetas.h"
#include "listaPoligonos.h"

typedef enum {
    MODO_NENHUM,
    MODO_PONTO,
    MODO_SELECAO,
    MODO_RETA,
    MODO_POLIGONO
} ModoDesenho;

typedef enum {
    MENU_INICIAL,
    APLICACAO_EXECUTANDO
} EstadoApp;

extern ModoDesenho modoAtual;
extern EstadoApp estadoAtual;
extern ListaPontos listaPontos;
extern ListaRetas listaRetas;
extern ListaPoligonos listaPoligonos;

//Para criar pré-visualização no segmento de reta
extern int criandoReta;
extern double retaTempX1, retaTempY1;
extern double retaTempX2, retaTempY2;

// Para pré-visualização do segmento do polígono
extern int mouseXPreview;
extern int mouseYPreview;
extern int criandoPoligono;
Poligono poligonoTemp;

//Para transformações
extern Ponto* pontoSelecionado;
extern struct reta* retaSelecionada;
extern Poligono* poliSelecionado;

#endif
