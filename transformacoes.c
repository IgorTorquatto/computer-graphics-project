#include "transformacoes.h"
#include <math.h>

// Função para multiplicar um ponto por uma matriz 3x3
void multiplicarMatrizPonto(const double matriz[3][3], Ponto *ponto) {
    double vetor[3] = { ponto->x, ponto->y, 1.0 };
    double resultado[3] = { 0.0, 0.0, 0.0 };

    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            resultado[i] = resultado[i] + matriz[i][j] * vetor[j];
        }
    }

    ponto->x = resultado[0];
    ponto->y = resultado[1];
}

// Função para transladar (mover) um ponto
void transladarPonto(Ponto *ponto, double deslocX, double deslocY) {
    const double matrizTranslacao[3][3] = {
        {1.0, 0.0, deslocX},
        {0.0, 1.0, deslocY},
        {0.0, 0.0, 1.0}
    };

    multiplicarMatrizPonto(matrizTranslacao, ponto);
}

// Função que cria a matriz de rotação em torno de um centro
void pegarMatrizRotacao(double matrizDestino[3][3], unsigned char tecla, Ponto centro) { //composta
    // ângulo de 2 graus em radianos
    double passoAngulo = 2 * (M_PI / 180.0);
    double cosseno = cos(passoAngulo);
    double seno = sin(passoAngulo);

    // matriz de rotação composta com translação
    double matrizRotacao[3][3] = {
        {cosseno, -seno, ((-cosseno * centro.x) + (seno * centro.y) + centro.x)},
        {seno,  cosseno, ((-seno * centro.x) - (cosseno * centro.y) + centro.y)},
        {0.0,    0.0,    1.0}
    };

    // copiando para matrizDestino
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDestino[i][j] = matrizRotacao[i][j];
        }
    }
}

// Função que aplica a matriz em um ponto
void aplicarMatrizNoPonto(double matriz[3][3], Ponto* p) {
    double xOriginal = p->x;
    double yOriginal = p->y;

    p->x = matriz[0][0] * xOriginal + matriz[0][1] * yOriginal + matriz[0][2];
    p->y = matriz[1][0] * xOriginal + matriz[1][1] * yOriginal + matriz[1][2];
}

