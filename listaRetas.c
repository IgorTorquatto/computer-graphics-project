#include "listaRetas.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void criarListaRetas(ListaRetas* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void ListaRetasInserirFim(ListaRetas* lista, Reta r) {
    NoReta* novo = (NoReta*)malloc(sizeof(NoReta));
    novo->reta = r;
    novo->prox = NULL;

    if (!lista->inicio) {
        lista->inicio = novo;
    } else {
        NoReta* atual = lista->inicio;
        while (atual->prox) atual = atual->prox;
        atual->prox = novo;
    }

    lista->tamanho++;
    printf("Total de retas: %d\n", lista->tamanho);
}

void desenharRetas(ListaRetas* lista) {
    NoReta* atual = lista->inicio;
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    while (atual) {
        if (atual->reta.selected) {
            glColor3f(1.0, 0.5, 0.0);  // Laranja se selecionada
        } else {
             glColor3f(1.0, 0.0, 0.0);
        }
        glVertex2d(atual->reta.x1, atual->reta.y1);
        glVertex2d(atual->reta.x2, atual->reta.y2);
        atual = atual->prox;
    }
    glEnd();
}

void selecionarRetaMaisProxima(ListaRetas* lista, double x, double y) {
    NoReta* atual = lista->inicio;
    while (atual) {
        // Seleciona se o ponto está próximo da reta (tolerância de 5 pixels)
        double dx = atual->reta.x2 - atual->reta.x1;
        double dy = atual->reta.y2 - atual->reta.y1;
        double len = sqrt(dx * dx + dy * dy);
        if (len == 0) { atual = atual->prox; continue; }

        double t = ((x - atual->reta.x1) * dx + (y - atual->reta.y1) * dy) / (len * len);
        if (t >= 0 && t <= 1) {
            double proj_x = atual->reta.x1 + t * dx;
            double proj_y = atual->reta.y1 + t * dy;
            double dist = sqrt((x - proj_x) * (x - proj_x) + (y - proj_y) * (y - proj_y));
            if (dist <= 5.0) {
                atual->reta.selected = !atual->reta.selected;
                break;
            }
        }
        atual = atual->prox;
    }
}

void deletarRetasSelecionadas(ListaRetas* lista) {
    NoReta* atual = lista->inicio;
    NoReta* anterior = NULL;

    while (atual) {
        if (atual->reta.selected) {
            NoReta* temp = atual;
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                lista->inicio = atual->prox;
            }
            atual = atual->prox;
            free(temp);
            lista->tamanho--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    printf("Total de retas: %d\n", lista->tamanho);
}

