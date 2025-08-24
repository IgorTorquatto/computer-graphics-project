#include "listaPoligonos.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "estado.h"

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

    while (atual) {
        Poligono p = atual->poligono;

        if (p.selected)
            glColor3f(1.0, 0.5, 0.0); // laranja
        else
            glColor3f(1.0, 0.0, 0.0); // vermelho

        //preenchimento
        if (p.numVertices >= 3) {
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < p.numVertices; i++)
                glVertex2d(p.verticesX[i], p.verticesY[i]);
            glEnd();
        }

        //contorno
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < p.numVertices; i++)
            glVertex2d(p.verticesX[i], p.verticesY[i]);
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

void selecionarPoli(ListaPoligonos* lista, int x, int y){
    NoPoligono* atual = lista->inicio;
    int count = 0;

    while (atual) {
        atual->poligono.selected = 0;
        atual = atual->prox;
    }

    poliSelecionado = NULL; // reseta seleção

    // procura a primeira reta dentro da tolerância
    atual = lista->inicio;

    while(atual != NULL){
        // p recebe o primeiro da lista
        Poligono* p = &atual->poligono;
        count = 0;


        for(int i = 0; i < p->numVertices; i++){
            int j;
            if(i == p->numVertices-1){
                j = 0;
            }else{
                j = i+1;
            }
            int caso = 0;
            int esp = 0;

            if(i == 0){
                esp = p->numVertices-1;
            }else esp = i-1;

            //aqui a reta nao é selecionada;
            if((p->verticesY[i] > y && p->verticesY[j] > y) || (p->verticesY[i] < y && p->verticesY[j] < y) || (p->verticesX[i] < x && p->verticesX[j] < x)){
                caso = 1;
            }else if((p->verticesX[i] > x && p->verticesX[j] > x) && (p->verticesY[i] > y && p->verticesY[j] < y) || (p->verticesY[i] < y && p->verticesY[j] > y)){
                // caso nao trivial 1 - calcula se a reta é selecionada;
                caso = 2;
            }else if((p->verticesX[i] > x && p->verticesX[j] > x) && (p->verticesY[i] < y && p->verticesY[j] > y) || (p->verticesY[i] > y && p->verticesY[j] < y)){
                // caso nao trivial 2 - calcula se a reta é selecionada;
                caso = 2;
            }else if(p->verticesY[i] == y || p->verticesY[j] == y){
                // usar o ponto i;
                caso = 3;
            }

            if(p->verticesY[i] == p->verticesY[j] && p->verticesY[i] == y){
                //printf("Nao seleciona ne \n");
                count = count;
            }else if(caso == 1){
                count = count;
                //printf("Nao selecionada \n");
                //printf("Mouse x: %d , Mouse y: %d , Ponto 1 %f %f , Ponto 2 %f %f \n", x, y, p->verticesX[i], p->verticesY[i], p->verticesX[j], p->verticesY[j]);
            }else if(caso == 2){
                float xi;
                xi = p->verticesX[i] + ((y - p->verticesY[i])*(p->verticesX[j] - p->verticesX[i]) / (p->verticesY[j] - p->verticesY[i]));
                if(xi > (float)x){
                    count++;
                    //printf("%d Nao trivial para a reta %d\n",count,i);
                    //printf("Mouse x: %d , Mouse y: %d , Ponto 1 %f %f , Ponto 2 %f %f \n", x, y, p->verticesX[i], p->verticesY[i], p->verticesX[j], p->verticesY[j]);
                }
            }else if(caso == 3){
                if(p->verticesY[i] == y){
                    if((p->verticesY[esp] > y && p->verticesY[j] < y) || (p->verticesY[esp] < y && p->verticesY[j] > y)){
                        count++;
                    }else count = count;
                }else count = count;
            }else count = count;
        }
        if(count%2 != 0){
            p->selected = 1;
            poliSelecionado = &atual->poligono;
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
