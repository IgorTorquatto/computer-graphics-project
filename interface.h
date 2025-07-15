#ifndef INTERFACE_H
#define INTERFACE_H

#include "estruturas.h"

// Cria um bot�o com os par�metros fornecidos e o adiciona � p�gina
void criarBotao(ProgramPage *pg, int id, int x, int y, double width, double height, char *label, double rgb[3]);

// Cria e inicializa uma nova p�gina da aplica��o
int criar_pagina(ProgramPage *destino, int pageID, void (*pageFunction)(void));

// Adiciona um texto a uma p�gina
int add_text(ProgramPage *pg, char *msg, void *font, double xStart, double yStart);

// Cria um objeto texto (Text)
int criar_text(Text *destino, char *msg, void *font, double xStart, double yStart);

// Renderiza um texto na tela
void drawText(Text texto);

// Exibe todos os bot�es e textos da p�gina atual
void showPage(ProgramPage *pagina);

// Renderiza um bot�o individual na tela
void drawButton(Button *button);

// Verifica se um ponto est� dentro da �rea de um bot�o
int isPointInsideButton(int x, int y, Button button);

void desenharInterface();
void clickInterface(int x, int y);

#endif

