#include <GL/glut.h>
#include <math.h>
#include "menu.h"

#define windowWidth 800
#define windowHeight 600

EstadoApp estadoAtual = MENU_INICIAL;

Botao botoesMenu[] = {
    {300, 360, 200, 50, "Iniciar"},
    {300, 280, 200, 50, "Carregar"},
    {300, 200, 200, 50, "Sair"}
};

int numBotoes = sizeof(botoesMenu) / sizeof(Botao);

// Desenha texto no centro de um retângulo
void desenharTextoCentralizado(float x, float y, const char* texto, void* fonte) {
    float larguraTotal = 0;
    for (int i = 0; texto[i]; i++) {
        larguraTotal += glutBitmapWidth(fonte, texto[i]);
    }
    glRasterPos2f(x - larguraTotal / 2, y - 5);
    for (int i = 0; texto[i]; i++) {
        glutBitmapCharacter(fonte, texto[i]);
    }
}

// Desenha texto com espaçamento extra entre letras
void desenharTextoComEspaco(float x, float y, const char* texto, float espaco) {
    float posX = x;
    for (int i = 0; texto[i]; i++) {
        glRasterPos2f(posX, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
        posX += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, texto[i]) + espaco;
    }
}

// Desenha botão com fundo e borda
void desenharBotao(Botao b) {
    // Fundo
    glColor3f(0.2, 0.2, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(b.x, b.y);
    glVertex2f(b.x + b.largura, b.y);
    glVertex2f(b.x + b.largura, b.y + b.altura);
    glVertex2f(b.x, b.y + b.altura);
    glEnd();

    // Borda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(b.x, b.y);
    glVertex2f(b.x + b.largura, b.y);
    glVertex2f(b.x + b.largura, b.y + b.altura);
    glVertex2f(b.x, b.y + b.altura);
    glEnd();

    // Texto
    glColor3f(1.0, 1.0, 1.0);
    desenharTextoCentralizado(b.x + b.largura / 2, b.y + b.altura / 2 - 4, b.texto, GLUT_BITMAP_HELVETICA_18);
}

void desenharFormaGeometrica(float x, float y, int tipo) {
    switch (tipo % 4) {
        case 0: // círculo
            glBegin(GL_POLYGON);
            for (int i = 0; i < 30; i++) {
                float ang = 2 * 3.1415926f * i / 30;
                glVertex2f(x + cos(ang) * 10, y + sin(ang) * 10);
            }
            glEnd();
            break;
        case 1: // quadrado
            glBegin(GL_QUADS);
            glVertex2f(x - 10, y - 10);
            glVertex2f(x + 10, y - 10);
            glVertex2f(x + 10, y + 10);
            glVertex2f(x - 10, y + 10);
            glEnd();
            break;
        case 2: // triângulo
            glBegin(GL_TRIANGLES);
            glVertex2f(x, y + 12);
            glVertex2f(x - 10, y - 8);
            glVertex2f(x + 10, y - 8);
            glEnd();
            break;
        case 3: // retângulo
            glBegin(GL_QUADS);
            glVertex2f(x - 12, y - 6);
            glVertex2f(x + 12, y - 6);
            glVertex2f(x + 12, y + 6);
            glVertex2f(x - 12, y + 6);
            glEnd();
            break;
    }
}

void desenharFundoDecorado() {
    glColor3f(1.0, 1.0, 1.0); // cor branca para as formas
    int tipo = 0;
    for (int x = 40; x < windowWidth; x += 100) {
        for (int y = 40; y < windowHeight; y += 100) {
            desenharFormaGeometrica(x, y, tipo++);
        }
    }
}

// Renderiza menu
void desenharMenuInicial() {
    glClear(GL_COLOR_BUFFER_BIT);

    desenharFundoDecorado(); // fundo decorado com formas

    // Título
    const char* titulo = "PAINT";
    float larguraTotal = 0;
    for (int i = 0; titulo[i]; i++)
        larguraTotal += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, titulo[i]) + 10;
    larguraTotal -= 10;

    glColor3f(0.2, 0.2, 0.5);
    desenharTextoComEspaco(((windowWidth - larguraTotal) / 2)+10, 470, titulo, 10);

    for (int i = 0; i < numBotoes; i++) {
        desenharBotao(botoesMenu[i]);
    }
}

int cliqueDentroDoBotao(Botao b, int mx, int my) {
    return (mx >= b.x && mx <= b.x + b.largura &&
            my >= b.y && my <= b.y + b.altura);
}

// Callback de clique do mouse
void mouseClick(int button, int state, int x, int y) {
    if (estadoAtual == MENU_INICIAL && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int mouseYInvertido = windowHeight - y;

        for (int i = 0; i < numBotoes; i++) {
            if (cliqueDentroDoBotao(botoesMenu[i], x, mouseYInvertido)) {
                switch (i) {
                    case 0:
                        estadoAtual = APLICACAO_EXECUTANDO;
                        break;
                    case 1:
                        // carregar projeto
                        break;
                    case 2:
                        exit(0);
                        break;
                }
            }
        }

        glutPostRedisplay();
    }
}
