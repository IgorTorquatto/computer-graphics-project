#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_INICIAL,
    APLICACAO_EXECUTANDO
} EstadoApp;

extern EstadoApp estadoAtual;

void desenharMenuInicial();
void mouseClick(int button, int state, int x, int y);
void desenharTextoCentralizado(float x, float y, const char* texto, void* fonte);

#endif
