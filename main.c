#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <string.h>
#include "menu.h"
#include "estruturas.h"
#include "interface.h"
#include "estado.h"
#include "listaPoligonos.h"

int windowWidth = 800;
int windowHeight = 600;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estadoAtual == MENU_INICIAL) {
        desenharMenuInicial();
    } else if (estadoAtual == APLICACAO_EXECUTANDO) {
        glColor3f(1, 1, 1);
        desenharInterface();

        // Desenhar preview da reta
        if (modoAtual == MODO_RETA && criandoReta) {
            glColor3f(1.0, 0.0, 0.0); // Vermelho
            glLineWidth(2.0);
            glBegin(GL_LINES);
            glVertex2i(retaTempX1, retaTempY1);
            glVertex2i(retaTempX2, retaTempY2);
            glEnd();
        }

        // Desenhar preview do segmento atual do polígono
        if (modoAtual == MODO_POLIGONO && criandoPoligono && poligonoTemp.numVertices > 0) {
            double lastX = poligonoTemp.verticesX[poligonoTemp.numVertices - 1];
            double lastY = poligonoTemp.verticesY[poligonoTemp.numVertices - 1];
            double tempX = mouseXPreview;
            double tempY = mouseYPreview;

            glColor3f(1.0, 0.0, 0.0); // Vermelho
            glLineWidth(2.0);
            glBegin(GL_LINES);
            glVertex2d(lastX, lastY);
            glVertex2d(tempX, tempY);
            glEnd();
        }
    }

    glutSwapBuffers();
}


void keyPress(unsigned char key, int x, int y) {

     if (modoAtual == MODO_POLIGONO && criandoPoligono && key == 13) { // tecla Enter
        if (poligonoTemp.numVertices >= 3) {
            ListaPoligonosInserirFim(&listaPoligonos, poligonoTemp);
        }
        criandoPoligono = 0;
        glutPostRedisplay();
    }


    if (key == 8) { // Backspace
        if (estadoAtual == APLICACAO_EXECUTANDO && modoAtual == MODO_SELECAO) {
            deletarSelecionados(&listaPontos);
            deletarRetasSelecionadas(&listaRetas);
            deletarPoligonosSelecionados(&listaPoligonos);
            glutPostRedisplay();
        }
    }
}


void init() {
    glClearColor(0.529, 0.808, 0.922, 1.0); // azul claro
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Trabalho Computação Gráfica");

    inicializarEstados();
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyPress);

    //Pré-visualização segmento de retae poligono
    glutMotionFunc(motionMouse);         // com botão pressionado
    glutPassiveMotionFunc(motionMouse);  // sem botão pressionado


    glutMainLoop();
    return 0;
}
