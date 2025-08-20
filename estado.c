#include "estado.h"
#include "interface.h"

ModoDesenho modoAtual = MODO_NENHUM;
EstadoApp estadoAtual = MENU_INICIAL;

ListaPontos listaPontos;
ListaRetas listaRetas;
ListaPoligonos listaPoligonos;

// Para criar pré-visualização do segmento de reta
int criandoReta = 0;
double retaTempX1, retaTempY1;
double retaTempX2, retaTempY2;

//Para a criação de polígonos
int criandoPoligono = 0;
int mouseXPreview = 0;
int mouseYPreview = 0;


void inicializarEstados() {
    criarListaPontos(&listaPontos);
    criarListaRetas(&listaRetas);
    criarListaPoligonos(&listaPoligonos);
}

//Para transformações
Ponto* pontoSelecionado = NULL;
struct reta* retaSelecionada = NULL;
Poligono* poliSelecionado = NULL;
