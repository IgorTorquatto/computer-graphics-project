#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "estado.h"
#include "save.h"

void salvarPontos(ListaPontos* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "wb");
    if (!f) { printf("Erro ao salvar pontos!\n"); return; }

    NoPonto* atual = lista->inicio;
    while (atual) {
        fwrite(&atual->ponto, sizeof(Ponto), 1, f);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarPontos(ListaPontos* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "rb");
    if (!f) { printf("Arquivo de pontos não encontrado!\n"); return; }

    criarListaPontos(lista);

    Ponto p;
    while (fread(&p, sizeof(Ponto), 1, f)) {
        NoPonto* novo = (NoPonto*)malloc(sizeof(NoPonto));
        novo->ponto = p;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->contador++;
    }
    fclose(f);
}

void salvarRetas(ListaRetas* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "wb");
    if (!f) return;

    NoReta* atual = lista->inicio;
    while (atual) {
        fwrite(&atual->reta, sizeof(Reta), 1, f);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarRetas(ListaRetas* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "rb");
    if (!f) return;

    lista->inicio = NULL;
    lista->tamanho = 0;

    Reta r;
    while (fread(&r, sizeof(Reta), 1, f)) {
        NoReta* novo = (NoReta*)malloc(sizeof(NoReta));
        novo->reta = r;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tamanho++;
    }
}

void salvarPoligonos(ListaPoligonos* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "wb");
    if (!f) return;

    NoPoligono* atual = lista->inicio;
    while (atual) {
        fwrite(&atual->poligono, sizeof(Poligono), 1, f);
        atual = atual->prox;
    }
    fclose(f);
}

void carregarPoligonos(ListaPoligonos* lista, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "rb");
    if (!f) return;

    lista->inicio = NULL;
    lista->tamanho = 0;

    Poligono p;
    while (fread(&p, sizeof(Poligono), 1, f)) {
        NoPoligono* novo = (NoPoligono*)malloc(sizeof(NoPoligono));
        novo->poligono = p;
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tamanho++;
    }
    fclose(f);
}

void salvarTudo() {
    salvarPontos(&listaPontos, "pontos.dat");
    salvarRetas(&listaRetas, "retas.dat");
    salvarPoligonos(&listaPoligonos, "poligonos.dat");
    printf("Todos os objetos salvos!\n");
}

void carregarTudo() {
    carregarPontos(&listaPontos, "pontos.dat");
    carregarRetas(&listaRetas, "retas.dat");
    carregarPoligonos(&listaPoligonos, "poligonos.dat");
    printf("Todos os objetos carregados!\n");
}

