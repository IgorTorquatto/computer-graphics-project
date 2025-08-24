#include <GL/glut.h>
#include <math.h>
#include "menu.h"
#include "estruturas.h"
#include "estado.h"
#include "interface.h"
#include "listaPoligonos.h"
#include "save.h"

#define windowWidth 800
#define windowHeight 600

Botao botoesMenu[] = {
    {300, 360, 200, 50, "Iniciar"},
    {300, 280, 200, 50, "Carregar"},
    {300, 200, 200, 50, "Sair"}
};

int numBotoes = sizeof(botoesMenu) / sizeof(Botao);

// pra onverter as coordenadas do mouse para coordenadas lógicas e funcionar na tela cheia
void converterCoordenadasMouse(int mx, int my, double* xL, double* yL) {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    // calcula escala em x e y
    double scaleX = (double)windowWidth / w;
    double scaleY = (double)windowHeight / h;

    // coordenadas lógicas
    *xL = mx * scaleX;
    *yL = windowHeight - (my * scaleY); // inverte Y
}


int cliqueDentroDoBotao(Botao b, int mx, int my) {
    double xL, yL;
    converterCoordenadasMouse(mx, my, &xL, &yL);

    return (xL >= b.x && xL <= b.x + b.largura &&
            yL >= b.y && yL <= b.y + b.altura);
}

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
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
        posX += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]) + espaco;
    }
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
    const char* titulo = "TRABALHO";
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

void mouseClick(int button, int state, int mx, int my) {
    static int retaEmAndamento = 0;
    static double tempX, tempY;

    if(button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    // Converte para coordenadas lógicas
    double xL, yL;
    converterCoordenadasMouse(mx, my, &xL, &yL);

    if (estadoAtual == MENU_INICIAL) {
        for (int i = 0; i < numBotoes; i++) {
            if (cliqueDentroDoBotao(botoesMenu[i], mx, my)) { // cliqueDentroDoBotao já faz a conversão
                switch (i) {
                    case 0:
                        estadoAtual = APLICACAO_EXECUTANDO;
                        break;
                    case 1:
                        carregarTudo();
                        estadoAtual = APLICACAO_EXECUTANDO;
                        break;
                    case 2:
                        exit(0);
                        break;
                }
                glutPostRedisplay();
                return;
            }
        }
    }

    else if (estadoAtual == APLICACAO_EXECUTANDO) {
        int clicouEmBotao = 0;

        clickInterface(xL, yL);

        // Verifica se o clique foi sobre algum botão
        if (cliqueDentroBotaoPonto(xL, yL) ||
            cliqueDentroBotaoSair(xL, yL) ||
            cliqueDentroBotaoReta(xL, yL) ||
            cliqueDentroBotaoPoligono(xL, yL) ||
            cliqueDentroBotaoSalvar(xL, yL) ||
            cliqueDentroBotaoSelecao(xL, yL)) {
            clicouEmBotao = 1;
        }

        if (modoAtual == MODO_PONTO && !clicouEmBotao) {
            inserirPonto(&listaPontos, xL, yL);
        }

        else if (modoAtual == MODO_SELECAO && !clicouEmBotao) {
            selecionarPontoMaisProximo(&listaPontos, xL, yL);
            selecionarRetaMaisProxima(&listaRetas, xL, yL);
            selecionarPoli(&listaPoligonos, xL, yL);
        }

        else if (modoAtual == MODO_RETA && !clicouEmBotao) {
            if (!criandoReta) {
                retaTempX1 = xL;
                retaTempY1 = yL;
                criandoReta = 1;
            } else {
                retaTempX2 = xL;
                retaTempY2 = yL;

                Reta r;
                r.id = listaRetas.tamanho + 1;
                r.x1 = retaTempX1;
                r.y1 = retaTempY1;
                r.x2 = retaTempX2;
                r.y2 = retaTempY2;
                r.selected = 0;
                r.rgb_color[0] = 1.0;
                r.rgb_color[1] = 0.0;
                r.rgb_color[2] = 0.0;

                ListaRetasInserirFim(&listaRetas, r);
                criandoReta = 0;
            }
        }

        else if (modoAtual == MODO_POLIGONO && !clicouEmBotao) {
            if (!criandoPoligono) {
                criandoPoligono = 1;
                poligonoTemp.id = listaPoligonos.tamanho;
                poligonoTemp.numVertices = 0;
                poligonoTemp.rgb_color[0] = 1.0;
                poligonoTemp.rgb_color[1] = 0.0;
                poligonoTemp.rgb_color[2] = 0.0;
                poligonoTemp.selected = 0;
            }

            if (poligonoTemp.numVertices < MAX_VERTICES) {
                poligonoTemp.verticesX[poligonoTemp.numVertices] = xL;
                poligonoTemp.verticesY[poligonoTemp.numVertices] = yL;
                poligonoTemp.numVertices++;
            }
        }

        glutPostRedisplay();
    }
}
