#include "listaRetas.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "estado.h"

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
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    while (atual) {
        if (atual->reta.selected) {
            glColor3f(1.0, 0.5, 0.0);  // laranja
        } else {
            glColor3f(1.0, 0.0, 0.0);
        }
        glVertex2d(atual->reta.x1, atual->reta.y1);
        glVertex2d(atual->reta.x2, atual->reta.y2);
        atual = atual->prox;
    }

    // Reta temporária (pré-visualização)
    if (modoAtual == MODO_RETA && criandoReta) {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(retaTempX1, retaTempY1);
        glVertex2d(retaTempX2, retaTempY2);
    }

    glEnd();
}

// calcular código de região

int codigo(double x, double y, double xmin, double xmax, double ymin, double ymax) {
    int code = 0; // 0000
    if (x < xmin) code |= 1;   // esquerda
    else if (x > xmax) code |= 2; // direita
    if (y < ymin) code |= 4;   // abaixo
    else if (y > ymax) code |= 8; // acima
    return code;
}

int pickReta(double x0, double y0, double x1, double y1, double mx, double my, double t) {
    double xmin = mx - t;
    double xmax = mx + t;
    double ymin = my - t;
    double ymax = my + t;

    int code0 = codigo(x0, y0, xmin, xmax, ymin, ymax);
    int code1 = codigo(x1, y1, xmin, xmax, ymin, ymax);

    while (1) {
        if ((code0 | code1) == 0) {
            // Totalmente dentro
            return 1;
        } else if (code0 & code1) {
            // Totalmente fora
            return 0;
        } else {
            double x, y;
            int outcodeOut = code0 ? code0 : code1;

            if (outcodeOut & 8) { // acima
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcodeOut & 4) { // abaixo
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcodeOut & 2) { // direita
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (outcodeOut & 1) { // esquerda
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (outcodeOut == code0) {
                x0 = x;
                y0 = y;
                code0 = codigo(x0, y0, xmin, xmax, ymin, ymax);
            } else {
                x1 = x;
                y1 = y;
                code1 = codigo(x1, y1, xmin, xmax, ymin, ymax);
            }
        }
    }
}

void selecionarRetaMaisProxima(ListaRetas* lista, int x, int y) {
    NoReta* atual = lista->inicio;
    double tolerancia = 5.0;

    // desmarca todas
    while (atual) {
        atual->reta.selected = 0;
        atual = atual->prox;
    }

    retaSelecionada = NULL; // reseta seleção

    // procura a primeira reta dentro da tolerância
    atual = lista->inicio;
    while (atual) {
        // check se o ponto (x, y) está perto da reta
        if (pickReta(atual->reta.x1, atual->reta.y1, atual->reta.x2, atual->reta.y2, x, y, tolerancia)) {
            atual->reta.selected = 1;
            retaSelecionada = &atual->reta; // guarda para usar no teclado
            break;
        }
        atual = atual->prox;
    }
}

void deletarRetasSelecionadas(ListaRetas* lista) {
    NoReta* atual = lista->inicio;
    NoReta* anterior = NULL;

    while (atual != NULL) {
        if (atual->reta.selected) {
            NoReta* temp = atual;

            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            atual = atual->prox;
            free(temp);
            lista->tamanho--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    printf("Retas restantes: %d\n", lista->tamanho);
}


