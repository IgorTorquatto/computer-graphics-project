#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#define MAX_VERTICES 100

// Definições de tipos
typedef struct ponto Ponto;
typedef struct reta Reta;

// Estrutura de ponto
struct ponto {
    int id;
    double x;
    double y;
    double rgb_color[3];
    int selected;
};

struct reta {
    int id;
    double x1, y1;
    double x2, y2;
    double rgb_color[3];
    int selected;
};

typedef struct poligono {
    int id;
    int numVertices;
    double verticesX[MAX_VERTICES];
    double verticesY[MAX_VERTICES];
    double rgb_color[3];
    int selected;
} Poligono;

#endif
