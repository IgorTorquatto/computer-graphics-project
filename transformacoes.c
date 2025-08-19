#include "transformacoes.h"

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
