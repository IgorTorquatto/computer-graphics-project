#ifndef LISTAPONTOS_H
#define LISTAPONTOS_H

#include <stdio.h>
#include "estruturas.h"

// Estrutura do nó da lista encadeada de pontos
typedef struct elemento {
    Ponto ponto;
    struct elemento *proximo;
} Elemento;

typedef struct elemento* ListaPontos;

// Funções principais da lista
ListaPontos* criarListaPontos();
void destruirListaPontos(ListaPontos *ldse);

int ListaPontosVazia(ListaPontos *ldse);
int ListaPontosInserirFim(ListaPontos *ldse, Ponto ponto);
int ListaPontosRemoverFim(ListaPontos *ldse);
int ListaPontosRemoverValor(ListaPontos *ldse, int id);
int ListaPontosAcessarIndice(ListaPontos *ldse, int pos, Ponto *ponto);
int ListaPontosAcessarValor(ListaPontos *ldse, int id, Ponto *ponto);

// Desenho e seleção
int desenhaPontos(ListaPontos *ldse);
Ponto *pickPontoIteration(ListaPontos *lista, int mouseX, int mouseY);

// Persistência
//void salvarListaPontos(FILE *fp, ListaPontos *lista);
//void carregarListaPontos(FILE *fp, EstadoExecucao *estado);

#endif // LISTAPONTOS_H

