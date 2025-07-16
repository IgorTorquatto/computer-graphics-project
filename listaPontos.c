#include <stdlib.h>
#include <GL/freeglut.h>
#include "listaPontos.h"

void criarListaPontos(ListaPontos* lista) {
    lista->inicio = NULL;
    lista->contador = 0;
}

void inserirPonto(ListaPontos* lista, double x, double y) {
    NoPonto* novo = (NoPonto*)malloc(sizeof(NoPonto));
    novo->ponto.id = lista->contador++;
    novo->ponto.x = x;
    novo->ponto.y = y;
    novo->ponto.rgb_color[0] = 1.0; // vermelho
    novo->ponto.rgb_color[1] = 0.0;
    novo->ponto.rgb_color[2] = 0.0;
    novo->ponto.selected = 0;
    novo->prox = lista->inicio;
    lista->inicio = novo;
    printf("Total de pontos: %d\n", lista->contador);
}

void desenharPontos(ListaPontos* lista) {
    NoPonto* atual = lista->inicio;
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    while (atual) {
        glColor3dv(atual->ponto.rgb_color);
        glVertex2d(atual->ponto.x, atual->ponto.y);
        atual = atual->prox;
    }
    glEnd();
}

