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
void criarMatrizRotPoli(Poligono *poli, double result[3][3]);
void aplicarMatrizNaReta(Reta* reta, double matriz[3][3]);
void aplicarMatrizNoPoli(Poligono* poli, double matriz[3][3]);
void rotacionarReta(Reta *reta);
void rotacionarPoli(Poligono *poli);
void cisalharReta(Reta *reta, int direcao);
void getCentroReta(Reta *reta,float *centrox,float *centroy);
void getCentroPoli(Poligono *poli, float *centrox, float *centroy);
void cisalharReta(Reta *reta, int direcao);
void cisalharPoli(Poligono *poli, int direcao);
void criarMatrizEscala(double result[3][3], double valor);
void escalarReta(Reta *reta,float valor);
void escalarPoli(Poligono *poli, float valor);
void refletirReta(Reta *reta, int direcao);
void refletirPoli(Poligono *poli, int direcao);

#endif

