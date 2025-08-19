#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include "estruturas.h"

void multiplicarMatrizPonto(const double matriz[3][3], Ponto *ponto);
void transladarPonto(Ponto *ponto, double deslocX, double deslocY);

#endif

