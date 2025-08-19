#include <stdlib.h>
#include <GL/freeglut.h>
#include "listaPontos.h"
#include "estado.h"

void criarListaPontos(ListaPontos* lista) {
    lista->inicio = NULL;
    lista->contador = 0;
}

void inserirPonto(ListaPontos* lista, double x, double y) {
    NoPonto* novo = (NoPonto*)malloc(sizeof(NoPonto));
    novo->ponto.id = lista->contador++;
    novo->ponto.x = x;
    novo->ponto.y = y;
    novo->ponto.rgb_color[0] = 1.0; // vermelho
    novo->ponto.rgb_color[1] = 0.0;
    novo->ponto.rgb_color[2] = 0.0;
    novo->ponto.selected = 0;
    novo->prox = lista->inicio;
    lista->inicio = novo;
    printf("Total de pontos: %d\n", lista->contador);
}

void desenharPontos(ListaPontos* lista) {
    NoPonto* atual = lista->inicio;
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    while (atual) {
        if (atual->ponto.selected)
            glColor3f(1.0, 0.5, 0.0); // cor laranja se estiver selecionado
        else
            glColor3dv(atual->ponto.rgb_color); // cor normal

        glVertex2d(atual->ponto.x, atual->ponto.y);
        atual = atual->prox;
    }
    glEnd();
}

//Igual vimos em sala: verificação por retângulo com tolerância
int pickPonto(float px, float py, float mx, float my, int t) {
    if (mx <= px + t && mx >= px - t) {
        if (my <= py + t && my >= py - t) {
            return 1; // dentro da área detectável
        }
    }
    return 0; // fora da área detectável
}


void selecionarPontoMaisProximo(ListaPontos* lista, int x, int y) {
    NoPonto* atual = lista->inicio;
    double tolerancia = 10.0;

    // desmarca todos
    while (atual) {
        atual->ponto.selected = 0;
        atual = atual->prox;
    }

    pontoSelecionado = NULL; //reseta seleção ADICIONADO PARA TRANSLACAO

    // procura o primeiro ponto dentro da tolerância
    atual = lista->inicio;
    while (atual) {
        if (pickPonto(atual->ponto.x, atual->ponto.y, x, y, tolerancia)) {
            atual->ponto.selected = 1;
            pontoSelecionado = &atual->ponto; //guarda para usar no teclado ADICIONADO PARA TRANSLACAO
            break;
        }
        atual = atual->prox;
    }
}

/*

void multiply_matriz_ponto(double matrizA[3][3], Ponto *destino) {
    double matrizPonto[3][1] = {destino->x, destino->y, 1};
    double result[3][1] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < 3; k++) {
                result[i][j] += matrizA[i][k] * matrizPonto[k][j];
            }
        }
    }

    destino->x = result[0][0];
    destino->y = result[1][0];
}*/
/*
void multiplicaMatrizes(int A[3][3], int colunasB, Ponto* ponto){
    int C[3][1] = {0};
    int B[3][1];
    int count = 0;
    int a,b;
    B[0][0] = ponto->x; B[1][0] = ponto->y; B[2][0] = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 1; j++) {
            C[i][j] = 0; // Inicializa o elemento
            for (int k = 0; k < 3; k++) {
                printf("Aqui?    aaaa\n");
                b = B[k][j];
                printf("AQUI");
                a = A[i][k];
                printf("Aquiiii");
                count = count + b*a;
                printf("Aqui? \n");
            }
            C[i][j] = count;
        }
    }
    ponto->x = C[0][0];
    ponto->y = C[1][0];
}


int** getMatrizT(int x, int y){
    int m[3][3];

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i == j){
                m[i][j] = 1;
            }else if(i==0 && j == 2){
                m[i][j] = x;
            }else if(i==1 && j==2){
                m[i][j] = y;
            }else m[i][j] = 0;
        }
    }

    return m;
}

void transladarPonto(ListaPontos* lista, int x, int y){
    int matriz = getMatrizT(x,y);
    int result[3][1];


    NoPonto* atual = lista->inicio;

    while(atual != NULL){
            if(atual->ponto.selected){
            multiplicaMatrizes(matriz,1,atual);
            printf("Aqui? \n");
        }
        atual = atual->prox;
    }
}
*/

void deletarSelecionados(ListaPontos* lista) {
    NoPonto* atual = lista->inicio;
    NoPonto* anterior = NULL;

    while (atual) {
        if (atual->ponto.selected) {
            NoPonto* temp = atual;
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            atual = atual->prox;
            free(temp);
            lista->contador--;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
    printf("Total de pontos apos exclusao: %d\n", lista->contador);
}


