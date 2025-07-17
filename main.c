#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <string.h>
#include "menu.h"
#include "estruturas.h"
#include "interface.h"
#include "estado.h"


int windowWidth = 800;
int windowHeight = 600;


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estadoAtual == MENU_INICIAL) {
        desenharMenuInicial();
    } else if (estadoAtual == APLICACAO_EXECUTANDO) {
        glColor3f(1, 1, 1);
        desenharInterface();
    }

    glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y) {
    if (key == 8) { // Backspace
        if (estadoAtual == APLICACAO_EXECUTANDO && modoAtual == MODO_SELECAO) {
            deletarSelecionados(&listaPontos);
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


    glutMainLoop();
    return 0;
}
