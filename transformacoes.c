#include "transformacoes.h"
#include <math.h>

// Fun��o para multiplicar um ponto por uma matriz 3x3
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

void criarMatrizTrans(double result[3][3],double deslocX, double deslocY){
    const double matrizTranslacao[3][3] = {
        {1.0, 0.0, deslocX},
        {0.0, 1.0, deslocY},
        {0.0, 0.0, 1.0}
    };

    for(int i = 0; i<3;i++){
        for(int j = 0; j<3; j++){
            result[i][j] = matrizTranslacao[i][j];
        }
    }
}

void multiplicarMatrizes(const double A[3][3],const double B[3][3],double result[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            result[i][j] = 0;
            for(int k = 0; k < 3; k++){
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void criarMatrizRotReta(Reta *reta, double result[3][3]){
    double A[3][3];
    double B[3][3];
    double C[3][3];

    double passoAngulo = 2 * (M_PI / 180.0);
    double cosseno = cos(passoAngulo);
    double seno = sin(passoAngulo);

    // matriz de rota��o composta com transla��o
    double matrizRotacao[3][3] = {
        {cosseno, -seno, 0.0},
        {seno,  cosseno, 0.0},
        {0.0,    0.0,    1.0}
    };


    double centrox = (reta->x1 + reta->x2)/2;
    double centroy = (reta->y1 + reta->y2)/2;


    criarMatrizTrans(A,-centrox,-centroy);
    criarMatrizTrans(B,centrox,centroy);
    multiplicarMatrizes(B,matrizRotacao,C);
    multiplicarMatrizes(C,A,result);
}

void criarMatrizRotPoli(Poligono *poli, double result[3][3]){
    double A[3][3];
    double B[3][3];
    double C[3][3];

    double passoAngulo = 2 * (M_PI / 180.0);
    double cosseno = cos(passoAngulo);
    double seno = sin(passoAngulo);

    // matriz de rota��o composta com transla��o
    double matrizRotacao[3][3] = {
        {cosseno, -seno, 0.0},
        {seno,  cosseno, 0.0},
        {0.0,    0.0,    1.0}
    };

    double centrox = 0;
    double centroy = 0;

    for(int i=0;i<poli->numVertices;i++){
        centrox += poli->verticesX[i];
        centroy += poli->verticesY[i];
    }
    centrox = centrox/poli->numVertices;
    centroy = centroy/poli->numVertices;

    criarMatrizTrans(A,-centrox,-centroy);
    criarMatrizTrans(B,centrox,centroy);
    multiplicarMatrizes(B,matrizRotacao,C);
    multiplicarMatrizes(C,A,result);
}

void aplicarMatrizNoPoli(Poligono* poli, double matriz[3][3]){
    Ponto ponto;
    for(int i=0; i< poli->numVertices;i++){
        ponto.x = poli->verticesX[i];
        ponto.y = poli->verticesY[i];
        multiplicarMatrizPonto(matriz,&ponto);
        poli->verticesX[i] = ponto.x;
        poli->verticesY[i] = ponto.y;
    }
}

void aplicarMatrizNaReta(Reta* reta, double matriz[3][3]){
    Ponto ponto;
    ponto.x = reta->x1;
    ponto.y = reta->y1;
    multiplicarMatrizPonto(matriz,&ponto);
    reta->x1 = ponto.x;
    reta->y1 = ponto.y;


    ponto.x = reta->x2;
    ponto.y = reta->y2;
    multiplicarMatrizPonto(matriz,&ponto);
    reta->x2 = ponto.x;
    reta->y2 = ponto.y;
}

void rotacionarReta(Reta *reta){
    double rot[3][3] = {0};
    criarMatrizRotReta(reta,rot);
    aplicarMatrizNaReta(reta,rot);
}

void rotacionarPoli(Poligono *poli){
    double rot[3][3] = {0};
    criarMatrizRotPoli(poli,rot);
    aplicarMatrizNoPoli(poli,rot);
}

// Fun��o para transladar (mover) um ponto
void transladarPonto(Ponto *ponto, double deslocX, double deslocY) {
    const double matrizTranslacao[3][3] = {
        {1.0, 0.0, deslocX},
        {0.0, 1.0, deslocY},
        {0.0, 0.0, 1.0}
    };

    multiplicarMatrizPonto(matrizTranslacao, ponto);
}

// Fun��o que cria a matriz de rota��o em torno de um centro
void pegarMatrizRotacao(double matrizDestino[3][3], unsigned char tecla, Ponto centro) { //composta
    // �ngulo de 2 graus em radianos
    double passoAngulo = 2 * (M_PI / 180.0);
    double cosseno = cos(passoAngulo);
    double seno = sin(passoAngulo);

    // matriz de rota��o composta com transla��o
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

// Fun��o que aplica a matriz em um ponto
void aplicarMatrizNoPonto(double matriz[3][3], Ponto* p) {
    double xOriginal = p->x;
    double yOriginal = p->y;

    p->x = matriz[0][0] * xOriginal + matriz[0][1] * yOriginal + matriz[0][2];
    p->y = matriz[1][0] * xOriginal + matriz[1][1] * yOriginal + matriz[1][2];
}

void aplicaMatrizReta(double m[3][3], double *x, double *y) {
    double xNovo = m[0][0] * (*x) + m[0][1] * (*y) + m[0][2] * 1.0;
    double yNovo = m[1][0] * (*x) + m[1][1] * (*y) + m[1][2] * 1.0;
    double w     = m[2][0] * (*x) + m[2][1] * (*y) + m[2][2] * 1.0;

    // Normalizar coordenadas homog�neas
    if (w != 0.0) {
        xNovo /= w;
        yNovo /= w;
    }

    *x = xNovo;
    *y = yNovo;
}

void transladarReta(Reta* reta, double dx, double dy) {
    if (reta == NULL) return;

    double matriz[3][3] = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1}
    };

    aplicaMatrizReta(matriz, &reta->x1, &reta->y1);
    aplicaMatrizReta(matriz, &reta->x2, &reta->y2);
}

void transladarPoli(Poligono *poli,double deslocX, double deslocY){
    Ponto ponto;
    for(int i = 0; i < poli->numVertices; i++){
        ponto.x = poli->verticesX[i];
        ponto.y = poli->verticesY[i];
        transladarPonto(&ponto, deslocX,deslocY);
        poli->verticesX[i] = ponto.x;
        poli->verticesY[i] = ponto.y;
    }
}

void getCentroReta(Reta *reta,float *centrox, float *centroy){
    *centrox = (reta->x1 + reta->x2)/2;
    *centroy = (reta->y1 + reta->y2)/2;
}

void getCentroPoli(Poligono *poli, float *centrox, float *centroy){
    *centrox = 0;
    *centroy = 0;

    for(int i=0; i<poli->numVertices; i++){
        *centrox += poli->verticesX[i];
        *centroy += poli->verticesY[i];
    }

    *centrox = *centrox/poli->numVertices;
    *centroy = *centroy/poli->numVertices;
}

void cisalharReta(Reta *reta, int direcao){
    double matrizh[3][3] = {{1,0.1,0},{0,1,0},{0,0,1}};
    double matrizv[3][3] = {{1,0,0},{0.1,1,0},{0,0,1}};
    float a,b;
    getCentroReta(reta,&a,&b);
    printf(" %f %f \n", a,b);
    printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);
    double trans[3][3];
    double result[3][3];

    switch(direcao){
    case 1: // cisalha horizontal;
        criarMatrizTrans(trans,(double)a,(double)b);
        multiplicarMatrizes(trans,matrizh,result);
        criarMatrizTrans(trans,(double)-a,(double)-b);
        multiplicarMatrizes(result,trans,matrizh);

        aplicarMatrizNaReta(reta,matrizh);
        getCentroReta(reta,&a,&b);
        printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);

        break;
    case 2: //cisalha vertical;
        criarMatrizTrans(trans,(double)a,(double)b);
        multiplicarMatrizes(trans,matrizv,result);
        criarMatrizTrans(trans,(double)-a,(double)-b);
        multiplicarMatrizes(result,trans,matrizv);

        aplicarMatrizNaReta(reta,matrizv);
        getCentroReta(reta,&a,&b);
        printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);
        break;
    }
}

void cisalharPoli(Poligono *poli, int direcao){
    double matrizh[3][3] = {{1,0.1,0},{0,1,0},{0,0,1}};
    double matrizv[3][3] = {{1,0,0},{0.1,1,0},{0,0,1}};
    float a,b;
    getCentroPoli(poli,&a,&b);
    //printf(" %f %f \n", a,b);
    //printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);
    double trans[3][3];
    double result[3][3];

    switch(direcao){
    case 1: // cisalha horizontal;
        criarMatrizTrans(trans,(double)a,(double)b);
        multiplicarMatrizes(trans,matrizh,result);
        criarMatrizTrans(trans,(double)-a,(double)-b);
        multiplicarMatrizes(result,trans,matrizh);

        aplicarMatrizNoPoli(poli,matrizh);
        //getCentroReta(reta,&a,&b);
        //printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);

        break;
    case 2: //cisalha vertical;
        criarMatrizTrans(trans,(double)a,(double)b);
        multiplicarMatrizes(trans,matrizv,result);
        criarMatrizTrans(trans,(double)-a,(double)-b);
        multiplicarMatrizes(result,trans,matrizv);

        aplicarMatrizNoPoli(poli,matrizv);
        //getCentroReta(reta,&a,&b);
        //printf(" ponto1 : %f %f, \n ponto2 : %f %f, \n centro %f %f \n",reta->x1,reta->y1,reta->x2,reta->y2,a,b);
        break;
    }
}

void criarMatrizEscala(double result[3][3], double valor){
    for(int i =0; i< 3; i++){
        for(int j = 0; j<3; j++){
            if((i==0 && j==0) || (i==1 && j==1)){
                result[i][j] = valor;
            }else if(i==2 && j== 2){
                result[i][j] = 1;
            }else result[i][j] = 0;
        }
    }
}

void escalarReta(Reta *reta,float valor){
    double escala[3][3] = {0};
    double aux[3][3] = {0};
    double result[3][3] = {0};
    float x,y;
    getCentroReta(reta,&x,&y);

    criarMatrizEscala(escala,valor);
    criarMatrizTrans(aux,(double)x,(double)y);
    multiplicarMatrizes(aux,escala,result);
    criarMatrizTrans(aux,(double)-x,(double)-y);
    multiplicarMatrizes(result,aux,escala);

    aplicarMatrizNaReta(reta,escala);

}

void escalarPoli(Poligono *poli, float valor){
    double escala[3][3] = {0};
    double aux[3][3] = {0};
    double result[3][3] = {0};
    float x,y;
    getCentroPoli(poli,&x,&y);

    criarMatrizEscala(escala,valor);
    criarMatrizTrans(aux,(double)x,(double)y);
    multiplicarMatrizes(aux,escala,result);
    criarMatrizTrans(aux,(double)-x,(double)-y);
    multiplicarMatrizes(result,aux,escala);

    aplicarMatrizNoPoli(poli,escala);
}

void refletirReta(Reta *reta, int direcao){
    double refletirH[3][3] = {{-1,0,0},{0,1,0},{0,0,1}};
    double refletirV[3][3] = {{1,0,0},{0,-1,0},{0,0,1}};
    double aux[3][3] = {0};
    double result[3][3] = {0};
    float x,y;
    getCentroReta(reta,&x,&y);

    if(direcao == 1){ // reflex�o horizontal
        criarMatrizTrans(aux,x,y);
        multiplicarMatrizes(aux,refletirH,result);
        criarMatrizTrans(aux,-x,-y);
        multiplicarMatrizes(result,aux,refletirH);
        aplicarMatrizNaReta(reta,refletirH);
    }else{
        criarMatrizTrans(aux,x,y);
        multiplicarMatrizes(aux,refletirV,result);
        criarMatrizTrans(aux,-x,-y);
        multiplicarMatrizes(result,aux,refletirV);
        aplicarMatrizNaReta(reta,refletirV);
    }

}

void refletirPoli(Poligono *poli, int direcao){
    double refletirH[3][3] = {{-1,0,0},{0,1,0},{0,0,1}};
    double refletirV[3][3] = {{1,0,0},{0,-1,0},{0,0,1}};
    double aux[3][3] = {0};
    double result[3][3] = {0};
    float x,y;
    getCentroPoli(poli,&x,&y);

    if(direcao == 1){ // reflex�o horizontal
        criarMatrizTrans(aux,x,y);
        multiplicarMatrizes(aux,refletirH,result);
        criarMatrizTrans(aux,-x,-y);
        multiplicarMatrizes(result,aux,refletirH);
        aplicarMatrizNoPoli(poli,refletirH);
    }else{
        criarMatrizTrans(aux,x,y);
        multiplicarMatrizes(aux,refletirV,result);
        criarMatrizTrans(aux,-x,-y);
        multiplicarMatrizes(result,aux,refletirV);
        aplicarMatrizNoPoli(poli,refletirV);
    }

}

