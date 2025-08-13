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
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    while (atual) {
        if (atual->ponto.selected)
            glColor3f(1.0, 0.5, 0.0); // cor laranja se estiver selecionado
        else
            glColor3dv(atual->ponto.rgb_color); // cor normal

        glVertex2d(atual->ponto.x, atual->ponto.y);
        atual = atual->prox;
    }
    glEnd();
}


void selecionarPontoMaisProximo(ListaPontos* lista, int x, int y) {
    double raioSelecao = 10.0; // tolerância
    NoPonto* atual = lista->inicio;

    while (atual) {
        double dx = atual->ponto.x - x;
        double dy = atual->ponto.y - y;
        double dist = sqrt(dx * dx + dy * dy);

        if (dist <= raioSelecao) {
            atual->ponto.selected = 1;
            break; // só seleciona um
        }

        atual = atual->prox;
    }
}


void deletarSelecionados(ListaPontos* lista) {
    NoPonto* atual = lista->inicio;
    NoPonto* anterior = NULL;

    while (atual) {
        if (atual->ponto.selected) {
            NoPonto* temp = atual;
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            atual = atual->prox;
            free(temp);
            lista->contador--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
    printf("Total de pontos apos exclusao: %d\n", lista->contador);
}

void transladarSelecionadosPontos(ListaPontos* lista, int x, int y){
    NoPonto* atual = lista->inicio;

    while(atual != NULL){
        if(atual->ponto.selected){
                atual->ponto.x += x;
                atual->ponto.y += y;
        }
        atual = atual->prox;
    }
}


