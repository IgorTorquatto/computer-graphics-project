#ifndef INTERFACE_H
#define INTERFACE_H

#include "estruturas.h"

// Cria um botão com os parâmetros fornecidos e o adiciona à página
void criarBotao(ProgramPage *pg, int id, int x, int y, double width, double height, char *label, double rgb[3]);

// Cria e inicializa uma nova página da aplicação
int criar_pagina(ProgramPage *destino, int pageID, void (*pageFunction)(void));

// Adiciona um texto a uma página
int add_text(ProgramPage *pg, char *msg, void *font, double xStart, double yStart);

// Cria um objeto texto (Text)
int criar_text(Text *destino, char *msg, void *font, double xStart, double yStart);

// Renderiza um texto na tela
void drawText(Text texto);

// Exibe todos os botões e textos da página atual
void showPage(ProgramPage *pagina);

// Renderiza um botão individual na tela
void drawButton(Button *button);

// Verifica se um ponto está dentro da área de um botão
int isPointInsideButton(int x, int y, Button button);

void desenharInterface();
void clickInterface(int x, int y);

#endif

