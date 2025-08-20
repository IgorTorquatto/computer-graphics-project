#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include "estruturas.h"

void multiplicarMatrizPonto(const double matriz[3][3], Ponto *ponto);
void transladarPonto(Ponto *ponto, double deslocX, double deslocY);
void pegarMatrizRotacao(double matrizDestino[3][3], unsigned char tecla, Ponto centro);
void aplicarMatrizNoPonto(double matriz[3][3], Ponto* p);
void transladarReta(Reta* reta, double dx, double dy);
void aplicaMatrizReta(double m[3][3], double *x, double *y);
void criarMatrizTrans(double result[3][3],double deslocX, double deslocY);
void multiplicarMatrizes(const double A[3][3],const double B[3][3],double result[3][3]);
void criarMatrizRotReta(Reta *reta, double result[3][3]);
void aplicarMatrizNaReta(Reta* reta, double matriz[3][3]);
void rotacionarReta(Reta *reta);

#endif

