#include "listaPoligonos.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

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

        if (p.selected) {
            glColor3f(1.0, 0.5, 0.0); // laranja para selecionados
        } else {
            glColor3f(1.0,0.0,0.0);
        }

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
    printf("Poligono criado. Total na lista: %d\n", lista->tamanho);
}

void selecionarPoligonoMaisProximo(ListaPoligonos* lista, int x, int y) {
    NoPoligono* atual = lista->inicio;
    const float distanciaMaxima = 10.0;

    while (atual != NULL) {
        Poligono* p = &atual->poligono;

        for (int i = 0; i < p->numVertices; i++) {
            float dx = p->verticesX[i] - x;
            float dy = p->verticesY[i] - y;
            float distancia = sqrt(dx * dx + dy * dy);

            if (distancia <= distanciaMaxima) {
                p->selected = !p->selected;
                return;
            }
        }

        atual = atual->prox;
    }
}

void selecionarPoli(ListaPoligonos* lista, int x, int y){
    NoPoligono* atual = lista->inicio;
    int count = 0;

    while(atual != NULL){
        // p recebe o primeiro da lista
        Poligono* p = &atual->poligono;
        count = 0;

        printf("---------------------------------- \n");

        for(int i = 0; i < p->numVertices; i++){
            //printf("%d para a reta %d \n", count,i);
            int j;

            if(i == p->numVertices-1){
                j = 0;
            }else{
                j = i+1;
            }

            // caso trivial
            if((p->verticesY[i] > y && p->verticesY[j] > y) || (p->verticesY[i] < y && p->verticesY[j] < y) || (p->verticesX[i] < x && p->verticesX[j] < x)){
                printf("Nao selecionada \n");
                printf("Mouse x: %d , Mouse y: %d , Ponto 1 %f %f , Ponto 2 %f %f \n", x, y, p->verticesX[i], p->verticesY[i], p->verticesX[j], p->verticesY[j]);
            }else if((p->verticesX[i] > x && p->verticesX[j] > x) && (p->verticesY[i] > y && p->verticesY[j] < y) || (p->verticesY[i] < y && p->verticesY[j] > y)){
                float xi;
                xi = p->verticesX[i] + ((y - p->verticesY[i])*(p->verticesX[j] - p->verticesX[i]) / (p->verticesY[j] - p->verticesY[i]));
                printf("o valor da intersecao eh: %d \n", xi);
                if(xi > (float)x){
                    count++;
                    printf("%d Nao trivial para a reta %d\n",count,i);
                    printf("Mouse x: %d , Mouse y: %d , Ponto 1 %f %f , Ponto 2 %f %f \n", x, y, p->verticesX[i], p->verticesY[i], p->verticesX[j], p->verticesY[j]);
                }

                /*count++;
                printf("%d No caso trivial para a reta %d\n", count,i);
                printf("Mouse x: %d , Mouse y: %d , Ponto 1 %f %f , Ponto 2 %f %f \n", x, y, p->verticesX[i], p->verticesY[i], p->verticesX[j], p->verticesY[j]);
                */
            }/*else{ // caso não trivial

            }*/

        }


        if(count%2 != 0){
            p->selected = !p->selected;
        }
        atual = atual->prox;
    }

}

void deletarPoligonosSelecionados(ListaPoligonos* lista) {
    NoPoligono* atual = lista->inicio;
    NoPoligono* anterior = NULL;

    while (atual != NULL) {
        if (atual->poligono.selected) {
            NoPoligono* apagar = atual;
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            atual = atual->prox;
            free(apagar);
            lista->tamanho--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
     printf("Total de poligonos apos exclusao: %d\n", lista->tamanho);
}
