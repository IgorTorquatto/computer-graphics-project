#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>

#define MAX_BUTTONS 10
#define MAX_TEXTS 10
#define MAX_CARACTERE 50
#define CLICK_TOLERANCE 10

// Enums de posição, cliques e páginas
typedef enum {
    TOP = 1,
    LEFT = 8,
    RIGHT = 4,
    BOTTOM = 2,
    INSIDE = 0
} positions;

typedef enum {
    cliqueNovoArquivo = 1,
    cliqueCarregarArquivo,
    cliqueCriarPontos,
    cliqueCriarRetas,
    cliqueCriarPoligonos,
    cliqueSalvarArquivo,
    cliqueSelecionarobjeto
} tiposCliques;

typedef enum {
    homePage = 50,
    drawPage,
    notFoundPage
} programPages;

// Definições de tipos
typedef struct botao Button;
typedef struct texto Text;
typedef struct ponto Ponto;
typedef struct reta Reta;
typedef struct poligono Poligono;
typedef struct elemento* ListaPontos;
typedef struct elemento_reta* ListaRetas;
typedef struct elemento_poli* ListaPoligonos;

// Estruturas de texto e botão
struct texto {
    char texto[MAX_CARACTERE];
    double xStart;
    double yStart;
    void *font;
};

struct botao {
    int id;
    int x;
    int y;
    double width;
    double height;
    Text label;
    double rgb[3];
    int ativo;
    int pressed;
};

// Página da aplicação
typedef struct {
    int pageID;
    void (*showPageFunction)(void);
    Button pageButtons[MAX_BUTTONS];
    Text pageTexts[MAX_TEXTS];
    int qtd_buttons;
    int qtd_texts;
} ProgramPage;

// Estrutura de ponto (objeto gráfico primário)
struct ponto {
    int id;
    double x;
    double y;
    double rgb_color[3];
    int selected;
};

// Estrutura de reta
struct reta {
    int id;
    Ponto ponto1;
    Ponto ponto2;
    Ponto centroide;
    double rgb_color[3];
    int selected;
};

// Estrutura de polígono
struct poligono {
    int id;
    int qtd_pontos;
    ListaPontos *pontos;
    Ponto centroide;
    double rgb_color[3];
    int selected;
};

#endif
