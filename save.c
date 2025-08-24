#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/freeglut.h>
#include "estruturas.h"
#include "estado.h"
#include "save.h"


void limparListaPontos(ListaPontos* lista){ //quando vou carregar um arquivo limpo as lista que estou estava usando
    if (!lista) return;
    NoPonto* atual = lista->inicio;
    while (atual) {
        NoPonto* t = atual;
        atual = atual->prox;
        free(t);
    }
    lista->inicio = NULL;
    lista->contador = 0;
}

void limparListaRetas(ListaRetas* lista) {
    if (!lista) return;
    NoReta* atual = lista->inicio;
    while (atual) {
        NoReta* t = atual;
        atual = atual->prox;
        free(t);
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void limparListaPoligonos(ListaPoligonos* lista) {
    if (!lista) return;
    NoPoligono* atual = lista->inicio;
    while (atual) {
        NoPoligono* t = atual;
        atual = atual->prox;
        free(t);
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
}


void salvarTela(const char* nomeArquivo, ListaPontos* lista_pt,ListaRetas* lista_rt,ListaPoligonos* lista_pol){//nomeArquivo é a string com o caminho/nome literal do arquivo

    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo \n");
        return;
    }

    if (lista_pt) {
        NoPonto* aux = lista_pt->inicio;
        while(aux != NULL){
            //id x y r g b
            fprintf(arquivo, "POINT %d %lf %lf %lf %lf %lf %d \n",
                    aux->ponto.id,
                    aux->ponto.x,
                    aux->ponto.y,
                    aux->ponto.rgb_color[0],
                    aux->ponto.rgb_color[1],
                    aux->ponto.rgb_color[2],
                    aux->ponto.selected);
            aux = aux->prox;
        }
    }


    if (lista_rt) {
        NoReta* aux2 = lista_rt->inicio;
        while(aux2 != NULL){
            //id x1 y1 x2 y2 r g b
            fprintf(arquivo, "LINE  %d %lf %lf %lf %lf %lf %lf %lf %d \n",
                    aux2->reta.id,
                    aux2->reta.x1, aux2->reta.y1,
                    aux2->reta.x2, aux2->reta.y2,
                    aux2->reta.rgb_color[0],
                    aux2->reta.rgb_color[1],
                    aux2->reta.rgb_color[2],
                    aux2->reta.selected);
            aux2 = aux2->prox;
        }
    }

      if (lista_pol) {
        NoPoligono* aux3 = lista_pol->inicio;
        while(aux3 != NULL){
            Poligono* P = &aux3->poligono;
            fprintf(arquivo, "POLY %d %d %lf %lf %lf %d",
                    P->id,
                    P->numVertices,
                    P->rgb_color[0],
                    P->rgb_color[1],
                    P->rgb_color[2],
                    P->selected);
            for (int i = 0; i < P->numVertices; ++i) {
                fprintf(arquivo, " %lf %lf", P->verticesX[i], P->verticesY[i]);
            }
            fprintf(arquivo, "\n");
            aux3 = aux3->prox;
        }
    }
    fclose(arquivo);
    printf("Lista salva em '%s'\n", nomeArquivo);
}



void carregarTela(const char* nomeArquivo, ListaPontos* lista_pt, ListaRetas* lista_rt, ListaPoligonos* lista_pol) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (!arquivo) {
        printf("Erro ao abrir arquivo para carregar");
    }

    //limpa listas atuais
    if (lista_pt) limparListaPontos(lista_pt);

    if (lista_rt) limparListaRetas(lista_rt);

    if (lista_pol) limparListaPoligonos(lista_pol);

    char tipo[16]; //guarda a palavra "poly,line..

    while (fscanf(arquivo, "%15s", tipo) == 1) {

        if (strcmp(tipo, "POINT") == 0) {
            Ponto p;
            fscanf(arquivo, "%d %lf %lf %lf %lf %lf %d",
                    &p.id, &p.x, &p.y,
                    &p.rgb_color[0],
                    &p.rgb_color[1],
                    &p.rgb_color[2],
                    &p.selected);
            ListaPontosInserirFim(lista_pt, p);
        }
         else if (strcmp(tipo, "LINE") == 0) {
            Reta r;
            fscanf(arquivo, "%d %lf %lf %lf %lf %lf %lf %lf %d",
                    &r.id, &r.x1, &r.y1, &r.x2, &r.y2,
                    &r.rgb_color[0],
                    &r.rgb_color[1],
                    &r.rgb_color[2],
                    &r.selected);
            ListaRetasInserirFim(lista_rt,r);
        }
         else if (strcmp(tipo, "POLY") == 0) {
            Poligono P;
            //%d %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.2lf
            fscanf(arquivo, "%d %d %lf %lf %lf %d",
                    &P.id, &P.numVertices,
                    &P.rgb_color[0],
                    &P.rgb_color[1],
                    &P.rgb_color[2],
                    &P.selected);

            for (int i = 0; i < P.numVertices; i++) {
                fscanf(arquivo, "%lf %lf", &P.verticesX[i], &P.verticesY[i]);
            }
            ListaPoligonosInserirFim(lista_pol,P);
        }
        else {
            // ignora tokens desconhecidos
        }
    }
    fclose(arquivo);
}
