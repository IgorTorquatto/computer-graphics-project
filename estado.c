#include "estado.h"
#include "interface.h"

ModoDesenho modoAtual = MODO_NENHUM;
EstadoApp estadoAtual = MENU_INICIAL;

ListaPontos listaPontos;
ListaRetas listaRetas;
ListaPoligonos listaPoligonos;

// Para criar pr�-visualiza��o do segmento de reta
int criandoReta = 0;
double retaTempX1, retaTempY1;
double retaTempX2, retaTempY2;

//Para a cria��o de pol�gonos
int criandoPoligono = 0;
int mouseXPreview = 0;
int mouseYPreview = 0;


void inicializarEstados() {
    criarListaPontos(&listaPontos);
    criarListaRetas(&listaRetas);
    criarListaPoligonos(&listaPoligonos);
}

//Para transforma��es
Ponto* pontoSelecionado = NULL;
struct reta* retaSelecionada = NULL;
Poligono* poliSelecionado = NULL;
