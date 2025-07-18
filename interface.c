#include <GL/glut.h>
#include "menu.h"
#include "estado.h"
#include "interface.h"
#include "listaPontos.h"
#include "listaRetas.h"

#define BTN_X 10
#define BTN_Y 560
#define BTN_W 80
#define BTN_H 30

#define RT_X 100
#define RT_Y 560
#define RT_W 80
#define RT_H 30

#define POL_X 190
#define POL_Y 560
#define POL_W 80
#define POL_H 30

#define SEL_X 280
#define SEL_Y 560
#define SEL_W 80
#define SEL_H 30

#define SLV_X 370
#define SLV_Y 560
#define SLV_W 80
#define SLV_H 30

#define SAI_X 460
#define SAI_Y 560
#define SAI_W 80
#define SAI_H 30

#define windowWidth 800
#define windowHeight 600

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

    // Desenha botão "Reta"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(RT_X, RT_Y);
    glVertex2f(RT_X + RT_W, RT_Y);
    glVertex2f(RT_X + RT_W, RT_Y + RT_H);
    glVertex2f(RT_X, RT_Y + RT_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(RT_X, RT_Y);
    glVertex2f(RT_X + RT_W, RT_Y);
    glVertex2f(RT_X+ RT_W, RT_Y + RT_H);
    glVertex2f(RT_X, RT_Y + RT_H);
    glEnd();

    // Desenha botão "Polígono"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(POL_X, POL_Y);
    glVertex2f(POL_X + POL_W, POL_Y);
    glVertex2f(POL_X + POL_W, POL_Y + POL_H);
    glVertex2f(POL_X, POL_Y + POL_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(POL_X, POL_Y);
    glVertex2f(POL_X + POL_W, POL_Y);
    glVertex2f(POL_X+ POL_W, POL_Y + POL_H);
    glVertex2f(POL_X, POL_Y + POL_H);
    glEnd();

    // Desenha botão "Seleção"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(SEL_X, SEL_Y);
    glVertex2f(SEL_X + SEL_W, SEL_Y);
    glVertex2f(SEL_X + SEL_W, SEL_Y + SEL_H);
    glVertex2f(SEL_X, SEL_Y + SEL_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(SEL_X, SEL_Y);
    glVertex2f(SEL_X + SEL_W, SEL_Y);
    glVertex2f(SEL_X+ SEL_W, SEL_Y + SEL_H);
    glVertex2f(SEL_X, SEL_Y + SEL_H);
    glEnd();

     // Desenha botão "Sair"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(SAI_X, SAI_Y);
    glVertex2f(SAI_X + SAI_W, SAI_Y);
    glVertex2f(SAI_X + SAI_W, SAI_Y + SAI_H);
    glVertex2f(SAI_X, SAI_Y + SAI_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(SAI_X, SAI_Y);
    glVertex2f(SAI_X + SAI_W, SAI_Y);
    glVertex2f(SAI_X+ SAI_W, SAI_Y + SAI_H);
    glVertex2f(SAI_X, SAI_Y + SAI_H);
    glEnd();

     // Desenha botão "Salvar"
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(SLV_X, SLV_Y);
    glVertex2f(SLV_X + SLV_W, SLV_Y);
    glVertex2f(SLV_X + SLV_W, SLV_Y + SLV_H);
    glVertex2f(SLV_X, SLV_Y + SLV_H);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(SLV_X, SLV_Y);
    glVertex2f(SLV_X + SLV_W, SLV_Y);
    glVertex2f(SLV_X+ SLV_W, SLV_Y + SLV_H);
    glVertex2f(SLV_X, SLV_Y + SLV_H);
    glEnd();

    glColor3f(1, 1, 1);
    desenharTextoCentralizado(BTN_X + BTN_W/2, (BTN_Y + BTN_H/2 - 4)+5, "Ponto", GLUT_BITMAP_HELVETICA_12);
    glColor3f(1, 1, 1);
    desenharTextoCentralizado(RT_X + RT_W/2, (RT_Y + RT_H/2 - 4)+5, "Reta", GLUT_BITMAP_HELVETICA_12);
    glColor3f(1, 1, 1);
    desenharTextoCentralizado(POL_X + POL_W/2, (POL_Y + POL_H/2 - 4)+5, "Poligono", GLUT_BITMAP_HELVETICA_12);
    glColor3f(1, 1, 1);
    desenharTextoCentralizado(SEL_X + SEL_W/2, (SEL_Y + SEL_H/2 - 4)+5, "Selecao", GLUT_BITMAP_HELVETICA_12);
    glColor3f(1, 1, 1);
    desenharTextoCentralizado(SLV_X + SLV_W/2, (SLV_Y + SLV_H/2 - 4)+5, "Salvar", GLUT_BITMAP_HELVETICA_12);
    glColor3f(1, 1, 1);
    desenharTextoCentralizado(SAI_X + SAI_W/2, (SAI_Y + SAI_H/2 - 4)+5, "Sair", GLUT_BITMAP_HELVETICA_12);
    desenharPontos(&listaPontos);
    desenharRetas(&listaRetas);
    desenharPoligonos(&listaPoligonos);


  // Desenhar visualização do polígono em criação
if (criandoPoligono && poligonoTemp.numVertices > 0) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < poligonoTemp.numVertices; i++) {
        glVertex2f(poligonoTemp.verticesX[i], poligonoTemp.verticesY[i]);
    }
    glVertex2f(mouseXPreview, mouseYPreview); // preview até o mouse
    glEnd();
}


}

int cliqueDentroBotaoPonto(int x, int y) {
    return x >= BTN_X && x <= BTN_X + BTN_W &&
           y >= BTN_Y && y <= BTN_Y + BTN_H;
}

int cliqueDentroBotaoReta(int x, int y) {
    return x >= RT_X && x <= RT_X + RT_W &&
           y >= RT_Y && y <= RT_Y + RT_H;
}

int cliqueDentroBotaoPoligono(int x, int y) {
    return x >= POL_X && x <= POL_X + POL_W &&
           y >= POL_Y && y <= POL_Y + POL_H;
}

int cliqueDentroBotaoSelecao(int x, int y) {
    return x >= SEL_X && x <= SEL_X + SEL_W &&
           y >= SEL_Y && y <= SEL_Y + SEL_H;
}

int cliqueDentroBotaoSalvar(int x, int y) {
    return x >= SLV_X && x <= SLV_X + SLV_W &&
           y >= SLV_Y && y <= SLV_Y + SLV_H;
}

int cliqueDentroBotaoSair(int x, int y) {
    return x >= SAI_X && x <= SAI_X + SAI_W &&
           y >= SAI_Y && y <= SAI_Y + SAI_H;
}


void clickInterface(int x, int y) {
    if (cliqueDentroBotaoPonto(x, y)) {
        modoAtual = MODO_PONTO;
    }
    else if (cliqueDentroBotaoSelecao(x, y)) {
    modoAtual = MODO_SELECAO;
    }
    else if (cliqueDentroBotaoSair(x, y)) {
        estadoAtual = MENU_INICIAL;
        glutPostRedisplay();  // atualiza a tela com o menu
    }
    else if (cliqueDentroBotaoReta(x, y)) {
        modoAtual = MODO_RETA;
    }
    else if (cliqueDentroBotaoPoligono(x, y)) {
    modoAtual = MODO_POLIGONO;
    criandoPoligono = 0;  // resetar estado anterior se necessário
    }
}

void motionMouse(int x, int y) {
    if (modoAtual == MODO_RETA && criandoReta) {
        retaTempX2 = x;
        retaTempY2 = windowHeight - y;
        glutPostRedisplay();
    }

    if (modoAtual == MODO_POLIGONO && criandoPoligono) {
        mouseXPreview = x;
        mouseYPreview = windowHeight - y;
        glutPostRedisplay();
    }
}


