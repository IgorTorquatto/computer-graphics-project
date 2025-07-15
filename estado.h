#ifndef ESTADO_H
#define ESTADO_H

#include "estruturas.h"
#include "listaPontos.h"

//Estrutura principal da aplica��o, armazena tudo que o programa precisa acessar: Lista de objetos criados
//Qual p�gina/menu o usu�rio est� , �ltimo objeto selecionado, �ltimo bot�o clicado...

typedef struct {
    int id;
    int lastObjectId;

    int qtd_pontos;
    ListaPontos *pontos_criados;

    int qtd_retas;
    ListaRetas *retas_criadas;

    int qtd_poligonos;
    ListaPoligonos *poligonos_criados;

    int currentPage;

    Ponto *lastPointSelected;
    Reta *lastLineSelected;
    Poligono *lastPolygonSelected;

    Button *lastButtonPressed;
} EstadoExecucao;

typedef enum {
    MODO_NENHUM,
    MODO_PONTO,
    // MODO_RETA, MODO_POLIGONO no futuro
} ModoDesenho;

extern ModoDesenho modoAtual;

// Inicializa o estado de execu��o da aplica��o
EstadoExecucao *criar_execucao(void);

// Libera todos os recursos associados ao estado
void destruir_execucao(EstadoExecucao *estado);

#endif
