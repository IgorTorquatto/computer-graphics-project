#include "listaPoligonos.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "estado.h"

//Graham
//Ponto base para ordenação polar
PontoGraham pontoBase;

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

        // Define cor do contorno
        if (p.selected)
            glColor3f(1.0, 0.5, 0.0); // laranja se selecionado
        else
            glColor3f(1.0, 0.0, 0.0); // vermelho caso contrário

        // Desenha apenas o contorno
        if (p.numVertices >= 2) {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < p.numVertices; i++)
                glVertex2d(p.verticesX[i], p.verticesY[i]);
            glEnd();
        }

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

    poliSelecionado = NULL; // reseta sele��o

    // procura a primeira reta dentro da toler�ncia
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

            //aqui a reta nao � selecionada;
            if((p->verticesY[i] > y && p->verticesY[j] > y) || (p->verticesY[i] < y && p->verticesY[j] < y) || (p->verticesX[i] < x && p->verticesX[j] < x)){
                caso = 1;
            }else if(((p->verticesX[i] > x && p->verticesX[j] > x) && (p->verticesY[i] > y && p->verticesY[j] < y)) || (p->verticesY[i] < y && p->verticesY[j] > y)){
                // caso nao trivial 1 - calcula se a reta � selecionada;
                caso = 2;
            }else if(((p->verticesX[i] > x && p->verticesX[j] > x) && (p->verticesY[i] < y && p->verticesY[j] > y)) || (p->verticesY[i] > y && p->verticesY[j] < y)){
                // caso nao trivial 2 - calcula se a reta � selecionada;
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

// Retorna a orientação de três pontos
// 0 = colinear, 1 = horário, 2 = anti-horário
int orientacao(PontoGraham p, PontoGraham q, PontoGraham r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;       // colinear
    return (val > 0) ? 1 : 2;     // 1 = horário, 2 = anti-horário
}

// Distância ao quadrado entre dois pontos
double distanciaQuad(PontoGraham p1, PontoGraham p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// Comparação para ordenação polar em relação ao pontoBase
int compararPontos(const void *vp1, const void *vp2) {
    PontoGraham *p1 = (PontoGraham *)vp1;
    PontoGraham *p2 = (PontoGraham *)vp2;

    int o = orientacao(pontoBase, *p1, *p2);
    if (o == 0) {
        // Se colinear, manter o mais distante do ponto base
        return (distanciaQuad(pontoBase, *p2) >= distanciaQuad(pontoBase, *p1)) ? -1 : 1;
    }
    return (o == 2) ? -1 : 1; // anti-horário vem antes
}

// Verifica se um polígono é convexo
int poligonoEhConvexo(Poligono *p) {
    if (p->numVertices < 3) return 0;

    int sentido = 0;
    for (int i = 0; i < p->numVertices; i++) {
        int j = (i + 1) % p->numVertices;
        int k = (i + 2) % p->numVertices;

        double dx1 = p->verticesX[j] - p->verticesX[i];
        double dy1 = p->verticesY[j] - p->verticesY[i];
        double dx2 = p->verticesX[k] - p->verticesX[j];
        double dy2 = p->verticesY[k] - p->verticesY[j];

        double cross = dx1 * dy2 - dy1 * dx2;
        if (cross != 0) {
            int novoSentido = (cross > 0) ? 1 : -1;
            if (sentido == 0) sentido = novoSentido;
            else if (sentido != novoSentido) return 0;
        }
    }
    return 1;
}

// Varredura de Graham para transformar polígono em convexo
void grahamConvexo(Poligono *p) {
    if (p->numVertices < 3) return;

    // Copiar vértices para PontoGraham
    PontoGraham pts[MAX_VERTICES];
    for (int i = 0; i < p->numVertices; i++) {
        pts[i].x = p->verticesX[i];
        pts[i].y = p->verticesY[i];
    }

    // Passo 1: escolher ponto base (menor Y, menor X em caso de empate)
    int min_idx = 0;
    for (int i = 1; i < p->numVertices; i++) {
        if (pts[i].y < pts[min_idx].y || (pts[i].y == pts[min_idx].y && pts[i].x < pts[min_idx].x)) {
            min_idx = i;
        }
    }
    PontoGraham temp = pts[0];
    pts[0] = pts[min_idx];
    pts[min_idx] = temp;
    pontoBase = pts[0];

    // Passo 2: ordenar pelos ângulos polares
    qsort(&pts[1], p->numVertices - 1, sizeof(PontoGraham), compararPontos);

    // Passo 3: remover pontos colineares consecutivos (mantendo o mais distante)
    int m = 1;
    for (int i = 1; i < p->numVertices; i++) {
        while (i < p->numVertices - 1 && orientacao(pontoBase, pts[i], pts[i + 1]) == 0) i++;
        pts[m++] = pts[i];
    }

    if (m < 3) return; // não forma polígono

    // Passo 4 e 5: construir a casca convexa usando pilha
    PontoGraham pilha[MAX_VERTICES];
    int topo = 0;
    pilha[topo++] = pts[0];
    pilha[topo++] = pts[1];
    pilha[topo++] = pts[2];

    for (int i = 3; i < m; i++) {
        while (topo >= 2 && orientacao(pilha[topo - 2], pilha[topo - 1], pts[i]) != 2) {
            topo--; // remover topo da pilha se curva interna
        }
        pilha[topo++] = pts[i]; // adicionar ponto atual
    }

    // Atualizar polígono original
    for (int i = 0; i < topo; i++) {
        p->verticesX[i] = pilha[i].x;
        p->verticesY[i] = pilha[i].y;
    }
    p->numVertices = topo;
}
