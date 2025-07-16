#include "estado.h"

ModoDesenho modoAtual = MODO_NENHUM;
EstadoApp estadoAtual = MENU_INICIAL;

ListaPontos listaPontos;  // global

void inicializarEstados() {
    criarListaPontos(&listaPontos);
}
