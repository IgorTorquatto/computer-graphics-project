#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>

// Definições de tipos
typedef struct ponto Ponto;

// Estrutura de ponto
struct ponto {
    int id;
    double x;
    double y;
    double rgb_color[3];
    int selected;
};

#endif
