#include "listaPoligonos.h"
#include <stdlib.h>
#include <GL/glut.h>

void criarListaPoligonos(ListaPoligonos* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserirPoligonoFim(ListaPoligonos* lista, Poligono p) {
    NoPoligono* novo = malloc(sizeof(NoPoligono));
    novo->poligono = p;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        NoPoligono* temp = lista->inicio;
        while (temp->prox) temp = temp->prox;
        temp->prox = novo;
    }
    lista->tamanho++;
}

void desenharPoligonos(ListaPoligonos* lista) {
    NoPoligono* atual = lista->inicio;
    while (atual != NULL) {
        Poligono p = atual->poligono;
        glColor3f(p.selected ? 1.0 : 1.0, p.selected ? 0.5 : 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < p.numVertices; i++) {
            glVertex2d(p.verticesX[i], p.verticesY[i]);
        }
        glEnd();
        atual = atual->prox;
    }
}

void ListaPoligonosInserirFim(ListaPoligonos* lista, Poligono p) {
    NoPoligono* novo = (NoPoligono*)malloc(sizeof(NoPoligono));
    novo->poligono = p;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        NoPoligono* atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    lista->tamanho++;
}



