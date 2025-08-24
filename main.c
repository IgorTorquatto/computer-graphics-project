#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <string.h>
#include "menu.h"
#include "estruturas.h"
#include "interface.h"
#include "estado.h"
#include "listaPoligonos.h"
#include "listaPontos.h"
#include "transformacoes.h"

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

        // Desenhar preview do segmento atual do pol�gono
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

void teclado(unsigned char key, int x, int y) {

    if (modoAtual == MODO_POLIGONO && criandoPoligono && key == 13) { // Enter
        if (poligonoTemp.numVertices >= 3) {
            //insere o polígono temporário na lista
            ListaPoligonosInserirFim(&listaPoligonos, poligonoTemp);
            printf("Polígono criado com %d vértices\n", poligonoTemp.numVertices);
        } else {
            printf("Um polígono precisa ter pelo menos 3 vértices\n");
        }
        criandoPoligono = 0; //finaliza modo de criação
        glutPostRedisplay();
        return;
    }

    if (key == 8) { // Backspace
        if (estadoAtual == APLICACAO_EXECUTANDO && modoAtual == MODO_SELECAO) {
            deletarSelecionados(&listaPontos);
            deletarRetasSelecionadas(&listaRetas);
            deletarPoligonosSelecionados(&listaPoligonos);
            glutPostRedisplay();
            return;
        }
    }

    //Objetos Selecionados

    if (pontoSelecionado) {
        // ROTAÇÃO
        if (key == 'r') {
            printf("Rotacionando ponto\n");
            double matriz[3][3];
            Ponto centro = {0,0};
            pegarMatrizRotacao(matriz, key, centro);
            aplicarMatrizNoPonto(matriz, pontoSelecionado);
        }
    }
    else if (retaSelecionada) {
        // ROTAÇÃO
        if (key == 'r') {
            printf("Reta rodando\n");
            rotacionarReta(retaSelecionada);
        }
        // CISALHAMENTO
        else if (key == 'c') {
            printf("Reta cisalhando horizontalmente\n");
            cisalharReta(retaSelecionada, 1);
        }
        else if (key == 'v') {
            printf("Reta cisalhando verticalmente\n");
            cisalharReta(retaSelecionada, 2);
        }
        // ESCALA
        else if (key == 'm') {
            printf("Reta escalando (maior)\n");
            escalarReta(retaSelecionada, 1.5);
        }
        else if (key == 'n') {
            printf("Reta escalando (menor)\n");
            escalarReta(retaSelecionada, 0.666);
        }
        // ESPELHAMENTO
        else if (key == 'd') {
            printf("Reta espelhada horizontalmente\n");
            refletirReta(retaSelecionada, 1);
        }
        else if (key == 'w') {
            printf("Reta espelhada verticalmente\n");
            refletirReta(retaSelecionada, 2);
        }
    }
    else if (poliSelecionado) {
        // ROTAÇÃO
        if (key == 'r') {
            printf("Polígono rodando\n");
            rotacionarPoli(poliSelecionado);
        }
        // CISALHAMENTO
        else if (key == 'c') {
            printf("Polígono cisalhando horizontalmente\n");
            cisalharPoli(poliSelecionado, 1);
        }
        else if (key == 'v') {
            printf("Polígono cisalhando verticalmente\n");
            cisalharPoli(poliSelecionado, 2);
        }
        // ESCALA
        else if (key == 'm') {
            printf("Polígono escalando (maior)\n");
            escalarPoli(poliSelecionado, 1.5);
        }
        else if (key == 'n') {
            printf("Polígono escalando (menor)\n");
            escalarPoli(poliSelecionado, 0.666);
        }
        // ESPELHAMENTO
        else if (key == 'd') {
            printf("Polígono espelhado horizontalmente\n");
            refletirPoli(poliSelecionado, 1);
        }
        else if (key == 'w') {
            printf("Polígono espelhado verticalmente\n");
            refletirPoli(poliSelecionado, 2);
        }
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    double passo = 10.0;
    double dx = 0.0, dy = 0.0;

    switch (key) {
        case GLUT_KEY_LEFT:  dx = -passo; break;
        case GLUT_KEY_RIGHT: dx =  passo; break;
        case GLUT_KEY_UP:    dy =  passo; break;
        case GLUT_KEY_DOWN:  dy = -passo; break;
        default: return;
    }

    // TRANSLAÇÃO

    if (pontoSelecionado) {
        printf("transladando ponto \n");
        transladarPonto(pontoSelecionado, dx, dy);
    }

    if (retaSelecionada) {
        printf("transladando reta \n");
        transladarReta(retaSelecionada, dx, dy);
    }

    if(poliSelecionado){
        printf("transladando poligono \n");
        transladarPoli(poliSelecionado,dx,dy);
    }

    glutPostRedisplay();
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
    glutCreateWindow("Trabalho Computacao Grafica");

    inicializarEstados();
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(specialKeys);


    //Pr�-visualiza��o segmento de retae poligono
    glutMotionFunc(motionMouse);         // com bot�o pressionado
    glutPassiveMotionFunc(motionMouse);  // sem bot�o pressionado


    glutMainLoop();
    return 0;
}
