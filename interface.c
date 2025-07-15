#include <GL/glut.h>
#include "menu.h"
#include "estado.h"

#define BTN_X 10
#define BTN_Y 560
#define BTN_W 80
#define BTN_H 30

void desenharInterface() {
    // Desenha botão "Ponto"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(BTN_X, BTN_Y);
    glVertex2f(BTN_X + BTN_W, BTN_Y);
    glVertex2f(BTN_X + BTN_W, BTN_Y + BTN_H);
    glVertex2f(BTN_X, BTN_Y + BTN_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(BTN_X, BTN_Y);
    glVertex2f(BTN_X + BTN_W, BTN_Y);
    glVertex2f(BTN_X+ BTN_W, BTN_Y + BTN_H);
    glVertex2f(BTN_X, BTN_Y + BTN_H);
    glEnd();

    glColor3f(1, 1, 1);
    desenharTextoCentralizado(BTN_X + BTN_W/2, (BTN_Y + BTN_H/2 - 4)+5, "Ponto", GLUT_BITMAP_HELVETICA_12);
}

int cliqueDentroBotaoPonto(int x, int y) {
    return x >= BTN_X && x <= BTN_X + BTN_W &&
           y >= BTN_Y && y <= BTN_Y + BTN_H;
}

void clickInterface(int x, int y) {
    if (cliqueDentroBotaoPonto(x, y)) {
        modoAtual = MODO_PONTO;
    }
}

