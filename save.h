#ifndef SAVE_H
#define SAVE_H

#include "estruturas.h"
#include "estado.h"

void salvarPontos(ListaPontos* lista, const char* nomeArquivo);
void carregarPontos(ListaPontos* lista, const char* nomeArquivo);
void salvarRetas(ListaRetas* lista, const char* nomeArquivo);
void carregarRetas(ListaRetas* lista, const char* nomeArquivo);
void salvarPoligonos(ListaPoligonos* lista, const char* nomeArquivo);
void carregarPoligonos(ListaPoligonos* lista, const char* nomeArquivo);
void salvarTudo();
void carregarTudo();

#endif

