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
    glLineWidth(10.0f);
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

void transladarSelecionadosRetas(ListaRetas* lista, int x, int y){
    NoReta* atual = lista->inicio;

    while(atual != NULL){
        if(atual->reta.selected){
                atual->reta.x1 += x;
                atual->reta.x2 += x;
                atual->reta.y1 += y;
                atual->reta.y2 += y;
        }
        atual = atual->prox;
    }
}

/*void escalarSelecionadosRetas(ListaRetas* lista, int val){
    NoReta* atual = lista->inicio;

    float escala[3][3];

    escala[0][0] = val;
    escala[1][1] = val;
    escala[2][2] = 1;

    while(atual != NULL){
        if(atual->reta.selected){
                float centrox = (atual->reta.x1 + atual->reta.x2)/2;
                float centroy = (atual->reta.y1 + atual->reta.y2)/2;
                float trans[3][3] = {0};
                trans[0][0] = 1.0; trans[0][2] = -centrox; trans[1][1] = 1.0; trans[1][2] = -centroy; trans[2][2] = 1.0;
                float A1 = multiplicarMatrizes(trans,escala);
                trans[0][0] = 1.0; trans[0][2] = centrox; trans[1][1] = 1.0; trans[1][2] = centroy; trans[2][2] = 1.0;
                float B1 = multiplicarMatrizes(A1,trans);

                float ret[3][1]; ret [0][0] = atual->reta.x1; ret [1][0] = atual->reta.y1; ret[2][0] = 1;
                float fim[3][1] = {0};
                float temp = 0.0;

                // B1 * ret
                for(int i = 0; i < 3; i++){
                    temp = 0.0;
                    for(int j = 0; j < 3; j++){
                            fim[i][0] += B1[i][j] * ret[j][0];
                    }
                    //fim[i][0] = temp;
                }
                atual->reta.x1 = fim[0][0];atual->reta.y1 = fim[1][0];

                ret [0][0] = atual->reta.x2; ret [1][0] = atual->reta.y2; ret[2][0] = 1;
                for(int i = 0; i < 3; i++){
                    temp = 0.0;
                    for(int j = 0; j < 3; j++){
                            temp += B1[i][j] * ret[j][0];
                    }
                    fim[i][0] = temp;
                }
                atual->reta.x2 = fim[0][0];atual->reta.y2 = fim[1][0];




        }
    }
}
*/
