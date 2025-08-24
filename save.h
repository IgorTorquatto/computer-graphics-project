#ifndef SAVE_H
#define SAVE_H

#include "listaPontos.h"
#include "listaRetas.h"
#include "listaPoligonos.h"

void salvarTela(const char* nomeArquivo, ListaPontos* lista_pt, ListaRetas* lista_rt, ListaPoligonos* lista_pol);

void carregarTela(const char* nomeArquivo, ListaPontos* lista_pt, ListaRetas* lista_rt, ListaPoligonos* lista_pol);

#endif
