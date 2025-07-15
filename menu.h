#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_INICIAL,
    APLICACAO_EXECUTANDO
} EstadoApp;

typedef struct {
    float x, y, largura, altura;
    const char* texto;
} Botao;

extern EstadoApp estadoAtual;

void desenharMenuInicial();
void mouseClick(int button, int state, int x, int y);
void desenharTextoCentralizado(float x, float y, const char* texto, void* fonte);
void desenharTextoComEspaco(float x, float y, const char* texto, float espaco);
void desenharFundoDecorado();
void desenharBotao(Botao b);
void desenharFormaGeometrica(float x, float y, int tipo);
int cliqueDentroDoBotao(Botao b, int mx, int my);
void mouseClick(int button, int state, int x, int y);

#endif
