#ifndef INTERFACE_H
#define INTERFACE_H

#include "estruturas.h"

void desenharInterface();
void clickInterface(int x, int y);
int cliqueDentroBotaoPonto(int x, int y);
int cliqueDentroBotaoReta(int x, int y);
int cliqueDentroBotaoPoligono(int x, int y);
int cliqueDentroBotaoSair(int x, int y) ;
int cliqueDentroBotaoSelecao(int x, int y);
int cliqueDentroBotaoSalvar(int x, int y);
void clickInterface(int x, int y);
void converterCoordenadasMouseInterface(int mx, int my, double *xL, double *yL);
void motionMouse(int x, int y);

#endif
